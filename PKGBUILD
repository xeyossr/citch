pkgname=citch
pkgver=1.0.0
pkgrel=1
pkgdesc="A small, fast, and completely C++-written system fetch tool"
arch=('x86_64')
url="https://github.com/xeyossr/citch"
license=('MIT')
depends=('glibc')
makedepends=('git')
source=("git+https://github.com/xeyossr/citch.git")
sha256sums=('SKIP')

build() {
    cd "$srcdir/$pkgname"
    make
}

package() {
    cd "$srcdir/$pkgname"
    install -Dm755 citch "$pkgdir/usr/bin/citch"
    install -Dm644 README.md "$pkgdir/usr/share/doc/citch/README.md"
    install -Dm644 LICENSE "$pkgdir/usr/share/licenses/citch/LICENSE"
}

