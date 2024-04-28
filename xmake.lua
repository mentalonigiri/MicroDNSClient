target("dnsquery")
  set_kind("binary")
  set_default(false)
  add_files("src/MicroDNSClient.cpp")
  add_includedirs("include")
  add_defines("MICRODNSCLIENT_MAIN_WANTED")

target("MicroDNSClient")
  set_kind("shared")
  add_files("src/MicroDNSClient.cpp")
  add_includedirs("include")

