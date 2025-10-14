## Passos:

**1. Primeiro, instale as bibliotecas necessárias no terminal:**
```bash
pip install markdown xhtml2pdf
```

**2. Edite o arquivo `main.py`, é ele quem chama o conversor:**
```python
from conversor import markdown_to_pdf

# Seu texto Markdown
texto = """
# Meu Documento

Este é um exemplo de **texto em markdown**.

## Lista de itens
- Item 1
- Item 2
- Item 3
"""

# Converte para PDF
markdown_to_pdf(texto, "meu_documento")
```

**3. Execute o arquivo Python no terminal:**
```bash
python3 main.py
```

