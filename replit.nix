{ pkgs }: {
	deps = [
    pkgs.strace
		pkgs.clang_12
		pkgs.ccls
	];
}