# Maintainer: Aggelos Tselios <aggelostselios777@gmail.com>

pkgname="bluebox"
pkgver="0.3"
pkgrel="1"
epoch=
pkgdesc="A free and open source sandbox game, written in C, designed to be extremely lightweight."
arch=(x86_64)
url="https://github.com/AndroGR/Bluebox2D"
license=('GNU General Public License v3')
groups=()
depends=(glibc sdl2 sdl2_image sdl2_ttf)
makedepends=(cmake gcc make sdl2 sdl2_image sdl2_ttf)
checkdepends=()
optdepends=('sdl2_mixer: Required if you want to enable sound.'
            'xorg-server: Create window dialogs with X primitives.'
	    'freetype2: Open fonts for various operations.'
	    'wayland: Required for BX_USE_WAYLAND');
provides=(bluebox)
conflicts=(bluebox-git)
# Required for older packages
replaces=(bluebox-bin)
backup=()
options=()
install=
changelog=
source=()
noextract=()
md5sums=()
validpgpkeys=()

prepare() {
	echo " -> Starting package building at: $(date)."
	echo " -> Make sure to run makepkg -s ! Arch is a bit confusing on this topic, sorry."
	echo " -> Starting directory: $(pwd)."
}

build() {
	cd ..
	echo " -> Entered directory: $(pwd)"
	echo " -> Configuring the source code, this should take a few seconds."
	cmake . -B build
	echo " -> Getting into the binary folder."
	cd build
	echo " -> Current working directory: $(pwd)."
	echo " -> Started compilation, this should take a few seconds."
	make -j1
}

check() {
	echo " -> Finished building, moving on to packaging..."
}

package() {
	cd ..
	echo " -> Current directory: $(pwd)."
	echo " -> Creating filesystem directories at ${pkgdir}..."
	mkdir -p ${pkgdir}/usr/share/bluebox/fonts/
	mkdir -p ${pkgdir}/usr/share/applications
	mkdir -p ${pkgdir}/usr/bin
	echo " -> Moving data files in place..."
	cp res/stone.png ${pkgdir}/usr/share/bluebox/stone.png
	cp res/tree.png ${pkgdir}/usr/share/bluebox/tree.png
	cp res/sand.png ${pkgdir}/usr/share/bluebox/sand.png
	cp res/pwater.png ${pkgdir}/usr/share/bluebox/pwater.png
	cp res/grass.png ${pkgdir}/usr/share/bluebox/grass.png
	cp res/dirt.png ${pkgdir}/usr/share/bluebox/dirt.png
	cp res/building.png ${pkgdir}/usr/share/bluebox/building.png
	cp build/bluebox.bin ${pkgdir}/usr/bin/bluebox.bin
	cp res/Bluebox.desktop ${pkgdir}/usr/share/applications/Bluebox.desktop
	cp res/fonts/InterV.ttf ${pkgdir}/usr/share/bluebox/fonts/InterV.ttf
	cp res/logo.png ${pkgdir}/usr/share/bluebox/logo.png
	echo " -> Building successful !"
	echo " -> You can now start distributing or enjoying the game. Have fun !"
}
