/**
\file
\brief header-only library for resolving dns
names.

To build with test client, use
```
g++ -DMICRODNSCLIENT_MAIN_WANTED MicroDNSClient.cpp -o dnsquery
```
and run it like that
```
./dnsquery google.com lua.org
```

To avoid building implementation, use
```
g++ -DMICRODNSCLIENT_DEFINITION_DISABLED MicroDNSClient.cpp
```

Of course you can build just the dynamic library:
```
g++ -fPIC -shared -o libMicroDNSClient.so MicroDNSClient.cpp
```
*/

#ifndef MICRODNSCLIENT_H
#define MICRODNSCLIENT_H

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <vector>

/**
It can only get addresses for domain names.
Use the only static method.
*/
struct MicroDNSClient {

  /**
  simply get list of ipv6 and ipv4 ips as strings
  for domain name like example.com
  \param[in] hostname hostname to get ip list for
  \return list of ip addresses as vector<string>
  **/
  static std::vector<std::string>
  getAddressesForDomainName(std::string hostname);
};

#ifndef MICRODNSCLIENT_DEFINITION_DISABLED
std::vector<std::string>
MicroDNSClient::getAddressesForDomainName(std::string hostname) {
  std::vector<std::string> addrlist;

  struct addrinfo hints, *res, *res0;
  int error;
  int save_errno;
  int s;
  const char *cause = NULL;
  char ipstr[256];
  ipstr[0] = '\0';

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  error = getaddrinfo(hostname.c_str(), "www", &hints, &res0);
  if (error) {
    std::string err = gai_strerror(error);
    throw err;
  }
  for (res = res0; res; res = res->ai_next) {
    void *addr;

    if (res->ai_family == AF_INET) {
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
      addr = &(ipv4->sin_addr);
    } else if (res->ai_family == AF_INET6) {
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)res->ai_addr;
      addr = &(ipv6->sin6_addr);
    }

    inet_ntop(res->ai_family, addr, ipstr, res->ai_addrlen);
    // std::cout << ipstr << "\n";
    addrlist.push_back(ipstr);
    ipstr[0] = '\0';
  }
  freeaddrinfo(res0);

  return addrlist;
}

#ifdef MICRODNSCLIENT_MAIN_WANTED

int main(int argc, char *argv[]) {
  std::vector<std::string> addrlist;

  for (int i = 1; i < argc; i++) {
    std::string hostname = argv[i];
    std::cout << "Hostname: " << hostname << "\n";
    try {
      addrlist = MicroDNSClient::getAddressesForDomainName(hostname);
    } catch (std::string err) {
      std::cout << "Resolving error: " << err << "\n";
      continue;
    }
    std::cout << "Number of results: " << addrlist.size() << "\n";
    for (int i = 0; i < addrlist.size(); i++) {
      std::cout << "ip: " << addrlist[i] << "\n";
    }
  }
  return 0;
}

#endif // MICRODNSCLIENT_MAIN_WANTED

#endif // MICRODNSCLIENT_DEFINITION_DISABLED

#endif // MICRODNSCLIENT_H
