# MicroDNSClient
simple one-function library for getting list of ip addresses
for domain name.

## Building test binary
```
xmake build dnsquery
xmake run dnsquery google.com # will give you ip addresses for google.com
```

## Expected output
```
Hostname: google.com
Number of results: 10
ip: 108.177.97.138
ip: 108.177.97.102
ip: 108.177.97.101
ip: 108.177.97.100
ip: 108.177.97.113
ip: 108.177.97.139
ip: 2404:6800:4008:c13::66
ip: 2404:6800:4008:c13::8b
ip: 2404:6800:4008:c13::64
ip: 2404:6800:4008:c13::8a
```
