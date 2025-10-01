{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = {
    self,
    nixpkgs,
    ...
  } @ inputs: let
    systems = [
      "x86_64-linux"
    ];

    forAllSystems = f: nixpkgs.lib.genAttrs systems (system: f pkgsFor.${system});

    pkgsFor = nixpkgs.lib.genAttrs systems (
      system:
        import nixpkgs {
          inherit system;
          config.allowUnfree = true;
        }
    );
  in {
    formatter = forAllSystems (pkgs: pkgs.alejandra);

    devShells = forAllSystems (
      pkgs: {
        default = pkgs.mkShell {
          buildInputs = with pkgs; [
            pkgsi686Linux.glibc
          ];

          # NIX_LD_LIBRARY_PATH = with pkgs;
          #   lib.makeLibraryPath [
          #     glibc_multi
          #   ];
          #
          # NIX_LD = builtins.readFile "${pkgs.stdenv.cc}/nix-support/dynamic-linker";
          #
          # shellHook = ''
          #   export LD_LIBRARY_PATH="$NIX_LD_LIBRARY_PATH"
          # '';
        };
      }
    );
  };
}
