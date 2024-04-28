{ pkgs }: {
	deps = [
   pkgs.openssh
		pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}