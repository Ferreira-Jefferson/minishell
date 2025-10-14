import markdown
from xhtml2pdf import pisa
from io import BytesIO
import os

def markdown_to_pdf(markdown_text, output_filename):
    """
    Converte texto Markdown para PDF com formatação adequada.
    
    Args:
        markdown_text (str): Texto em formato Markdown
        output_filename (str): Nome do arquivo PDF de saída (com ou sem extensão .pdf)
    
    Returns:
        bool: True se a conversão foi bem-sucedida, False caso contrário
    """
    
    # Garante que o arquivo tenha extensão .pdf
    if not output_filename.endswith('.pdf'):
        output_filename += '.pdf'
    
    # Converte Markdown para HTML
    html = markdown.markdown(
        markdown_text,
        extensions=[
            'extra',
            'codehilite',
            'tables',
            'fenced_code',
            'nl2br'
        ]
    )
    
    # CSS para formatação do PDF
    css = """
    <style>
        @page {
            size: A4;
            margin: 2cm;
        }
        body {
            font-family: 'DejaVu Sans', Arial, sans-serif;
            font-size: 12pt;
            line-height: 1.6;
            color: #333;
        }
        h1 {
            color: #2c3e50;
            font-size: 24pt;
            margin-top: 20px;
            margin-bottom: 15px;
            border-bottom: 2px solid #3498db;
            padding-bottom: 10px;
        }
        h2 {
            color: #34495e;
            font-size: 20pt;
            margin-top: 18px;
            margin-bottom: 12px;
            border-bottom: 1px solid #bdc3c7;
            padding-bottom: 8px;
        }
        h3 {
            color: #34495e;
            font-size: 16pt;
            margin-top: 15px;
            margin-bottom: 10px;
        }
        p {
            margin-bottom: 10px;
            text-align: justify;
        }
        code {
            background-color: #f4f4f4;
            padding: 2px 6px;
            border-radius: 3px;
            font-family: 'Courier New', monospace;
            font-size: 10pt;
        }
        pre {
            background-color: #f4f4f4;
            padding: 15px;
            border-radius: 5px;
            border-left: 4px solid #3498db;
            overflow-x: auto;
            margin: 15px 0;
        }
        pre code {
            background-color: transparent;
            padding: 0;
        }
        table {
            border-collapse: collapse;
            width: 100%;
            margin: 15px 0;
        }
        th, td {
            border: 1px solid #bdc3c7;
            padding: 10px;
            text-align: left;
        }
        th {
            background-color: #3498db;
            color: white;
            font-weight: bold;
        }
        tr:nth-child(even) {
            background-color: #f9f9f9;
        }
        ul, ol {
            margin: 10px 0;
            padding-left: 30px;
        }
        li {
            margin-bottom: 5px;
        }
        blockquote {
            border-left: 4px solid #3498db;
            padding-left: 15px;
            margin: 15px 0;
            color: #555;
            font-style: italic;
        }
        a {
            color: #3498db;
            text-decoration: none;
        }
        hr {
            border: none;
            border-top: 2px solid #bdc3c7;
            margin: 20px 0;
        }
    </style>
    """
    
    # HTML completo com CSS
    html_with_css = f"""
    <!DOCTYPE html>
    <html>
    <head>
        <meta charset="UTF-8">
        {css}
    </head>
    <body>
        {html}
    </body>
    </html>
    """
    
    # Converte HTML para PDF
    try:
        with open(output_filename, 'wb') as pdf_file:
            pisa_status = pisa.CreatePDF(
                html_with_css,
                dest=pdf_file,
                encoding='UTF-8'
            )
        
        if pisa_status.err:
            print(f"Erro ao criar PDF: {pisa_status.err}")
            return False
        
        print(f"PDF criado com sucesso: {output_filename}")
        return True
    
    except Exception as e:
        print(f"Erro ao gerar PDF: {str(e)}")
        return False


# Exemplo de uso
if __name__ == "__main__":
    # Texto Markdown de exemplo
    exemplo_markdown = """
# Título Principal

Este é um documento de exemplo em **Markdown** que será convertido para PDF.

## Seção 1: Introdução

Este conversor suporta vários recursos do Markdown, incluindo:

- Listas com marcadores
- **Texto em negrito**
- *Texto em itálico*
- `código inline`

### Subseção 1.1

Você pode adicionar links como [este exemplo](https://www.python.org).

## Seção 2: Código

Aqui está um exemplo de bloco de código:

```python
def hello_world():
    print("Olá, mundo!")
    return True
```

## Seção 3: Tabelas

| Coluna 1 | Coluna 2 | Coluna 3 |
|----------|----------|----------|
| Dado 1   | Dado 2   | Dado 3   |
| Dado 4   | Dado 5   | Dado 6   |

## Seção 4: Citações

> Esta é uma citação importante que será formatada de forma especial.

---

**Nota:** Este é apenas um exemplo de documento Markdown.
"""
    
    # Converter para PDF
    markdown_to_pdf(exemplo_markdown, "documento_exemplo")
    
    # Ou use interativamente:
    # texto = input("Digite o texto Markdown: ")
    # nome_arquivo = input("Digite o nome do arquivo (sem extensão): ")
    # markdown_to_pdf(texto, nome_arquivo)