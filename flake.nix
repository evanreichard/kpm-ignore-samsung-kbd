{
  description = "ARM cross-compilation environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.05";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        buildInputs = with pkgs; [
          gnumake
          android-tools
          pkgsCross.aarch64-embedded.buildPackages.gcc
          pkgsCross.aarch64-embedded.buildPackages.binutils
        ];
      };
    };
}
