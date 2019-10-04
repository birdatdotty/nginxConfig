#include "Sections.h"

#include <QDebug>
#include <iostream>

int main()
{
  Location php, api;

  php << "include /etc/nginx/fastcgi_params"
      << "fastcgi_pass  127.0.0.1:9000"
      << "fastcgi_index index.php"
      << "fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name";

  api << "proxy_pass http://127.0.0.1:5555/";

  Section srv("server");

  srv << server(QStringList() << "dotty.su" << "test.local")
          << root("/tmp")
          << getLog("/tmp")
          << php.path("~ \\.php$")
          << api.path("= /api");

             std::cout << srv;
  return 0;
}
