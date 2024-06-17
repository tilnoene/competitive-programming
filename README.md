## QueryTree desatualizada

## Generating PDF

Requirements: [Python 3](https://www.python.org/), [pdflatex](http://pdftex.org).

### Ubuntu
```bash
sudo apt install python3
```

```bash
sudo apt install texlive texinfo texlive-fonts-recommended texlive-latex-extra
```

### Arch
```bash
yay -S python3
```

```bash
yay -S texlive texinfo texlive-fonts-recommended texlive-latex-extra
```

### Generating

After installing the above dependencies, run the following commands to generate the pdfs:

```bash
python3 generate_latex/generate_notebook.py
```

```bash
python3 generate_latex/generate_theoretical.py
```

After that, the pdf files will be in the project root folder ([notebook.pdf](notebook.pdf) and [notebook.pdf](theoretical.pdf)).
