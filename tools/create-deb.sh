#!/bin/bash
# This script creates an installable through dpkg / apt .deb file.
# It is needed for release v0.1.

srcdir=./../
HASBUILT="unknown"
_pkgdir=bluebox-0.1_1-amd64
function has_built() {
	if [ -f build/bluebox.bin ]; then
		echo " -> Package already built."
		# This doesn't really work so removed
	else
		echo "Package not built, so building now..."
		HASBUILT = "false"
	fi;
}

function usage() {
	echo "Usage: $0 [Arguments]"
	echo "Options:"
	echo "-c | Create a .deb package."
	echo "-h | Display this information."
	echo "-x | Clean up any useless files."
	return 0;
}

function buildpkg() {
	if ! [[ -d build/ ]]; then
		echo " -> Creating directory 'build/' in $(pwd)"
		mkdir build
		cd build
		echo " -> Building..."
		cmake ..
		make -j1
	else
		return -1;
	fi;
}

function prepare_() {
	echo " -> Starting at directory $(pwd)." 
	mkdir -p ${_pkgdir}/usr/share/applications
	mkdir -p ${_pkgdir}/usr/share/bluebox
	mkdir -p ${_pkgdir}/usr/bin
	mkdir -p ${_pkgdir}/usr/share/man/man1/
	mkdir -p ${_pkgdir}/DEBIAN/
}

function build() {
	echo " -> Building directory: $(pwd)."
	dpkg-deb --build --root-owner-group ${_pkgdir}
}
function create_pkg() {
	echo " -> Directory for 'create_pkg': $(pwd)."
	echo " -> Preparing..."
	prepare_
	echo " -> Finished preparing, moving data..."
	echo " -> Directory update: $(pwd)."
	cp tools/control ${_pkgdir}/DEBIAN/
	cp build/bluebox.bin ${_pkgdir}/usr/bin/
	cp res/Bluebox.desktop ${_pkgdir}/usr/share/applications
	cp res/*png ${_pkgdir}/usr/share/bluebox
	cp man/bluebox.1.gz ${_pkgdir}/usr/share/man/man1/
	echo " -> Finished data moving, now building..."
	build
	echo " -> Done."
	return 0
}
cd ..
if [[ -z $1 ]]; then
	usage
fi;

function cleanup() {
	rm -rf ${_pkgdir}
	rm -rf ${_pkgdir}.deb
}

while getopts ":chx" _opts; do
	case ${_opts} in
		c)
			has_built
			if [[ HASBUILT == "false" ]]; then
				echo " -> Warning: Compiling Bluebox because sources are invalid."
				buildpkg
				HASBUILT="true"
				create_pkg
			else
				echo " -> Sources verified."
				create_pkg
				HASBUILT="true"
			fi;
			;;
		h) 
			usage
			;;
		x) 
			cleanup
			;;
		*) 
			echo "$0:Unrecognized option."
			;;
	esac
done

