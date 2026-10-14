# Prerequisite

## Fedora

- Full 5GB Latex
```sh
sudo dnf upgrade --refresh
sudo dnf install -y git make gcc-c++ python3 texlive-scheme-full
```

- Minimalist
```sh
sudo dnf install -y \
  texlive-extsizes \
  texlive-listings \
  texlive-framed \
  texlive-titlesec \
  texlive-tocloft \
  texlive-fancyhdr \
  texlive-microtype \
  texlive-collection-fontsrecommended \
  texlive-amsmath \
  texlive-amsfonts
```
