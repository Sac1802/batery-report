pkgname=batery-report
pkgver=1.0
pkgrel=1
pkgdesc="Aplicación en C para monitorear el consumo de energía y la batería"
arch=('x86_64')
url="https://github.com/Sac1802/batery-report.git"
license=('MIT')
depends=('glibc')
source=("batery.c" "LICENSE")
sha256sums=('SKIP' 'SKIP')

build() {
  cd "$srcdir"
  gcc -o batery-report batery.c
}

package() {
  cd "$srcdir"
  install -Dm755 batery-report "$pkgdir/usr/bin/batery-report"
  install -Dm644 LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
}


