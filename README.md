C++11 Socket Class
==================

## Creating a Server Socket

```

net::serversocket* server = new net::serversocket(8080);
int err = server->listen();

if (err != 0) {
    std::cerr << strerror(err) << std::endl;
    exit(err);
}

while (true) {
    net::socket* client = server->accept();
    
    if (!client->valid()) {
        delete client;
        continue;
    }
}

```