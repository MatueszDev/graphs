import glob as g


paths = [
    'randomWalkDat_t/g4_u2_v4/',
    'randomWalkDat_t/g5_u1_v2/',
    'randomWalkDat_t/g5_u1_v4/',
    'randomWalkDat_t/g5_u2_v2/',
    'randomWalkDat_t/g6_u1_v2/',
    'randomWalkDat_t/g6_u2_v2/',
    'randomWalkDat_t/g7_u1_v2/',
]


text = '''\\documentclass[a4paper,12pt]{article}
\\usepackage{polski}
\\usepackage[utf8]{inputenc}
\\usepackage[T1]{fontenc}
\\usepackage{mathptmx}
\\usepackage{graphicx}
\\usepackage{amsmath}
\\usepackage[hidelinks]{hyperref}
\\usepackage{listings}
\\usepackage{float}
\\usepackage{longtable}
\\usepackage{grffile}
\\usepackage{color} %red, green, blue, yellow, cyan, magenta, black, white
\\usepackage{subfig}
\\definecolor{mygreen}{RGB}{28,172,0} % color values Red, Green, Blue
\\definecolor{mylilas}{RGB}{173,97,248}
\\definecolor{lbcolor}{RGB}{252,252,220}
\\definecolor{lbcolor}{rgb}{0.95,0.95,0.95}

\\usepackage{hyperref}
\\usepackage{pdfpages}
\\usepackage{caption}

\\usepackage{titling}
\\usepackage{indentfirst}
\\usepackage{geometry}
\\usepackage{setspace}
\\usepackage{wrapfig}
\\usepackage{multirow}
\\usepackage[table]{xcolor}
\\usepackage{tikz}
\\usetikzlibrary{shapes,arrows}
\\usepackage{alphalph}
\\renewcommand*{\\thesubfigure}{%
\\alphalph{\\value{subfigure}}%
}%
%\\geometry{hmargin={2cm, 2cm}, height=10.0in}
\\geometry{left=35mm, right=25mm, top=25mm, bottom=25mm}
\\makeatletter %only needed in preamble
\\renewcommand\\Huge{\\@setfontsize\\Huge{28pt}{18}}
\\renewcommand\\huge{\\@setfontsize\\huge{22pt}{18}}
\\renewcommand\\LARGE{\\@setfontsize\\LARGE{18pt}{18}}
\\renewcommand\\Large{\\@setfontsize\\Large{16pt}{18}}
\\renewcommand\\large{\\@setfontsize\\large{14pt}{18}}
\\renewcommand\\normalsize{\\@setfontsize\\normalsize{12pt}{18}}
\\renewcommand\\small{\\@setfontsize\\small{10pt}{18}}
\\renewcommand\\footnotesize{\\@setfontsize\\Large{10pt}{18}}
\\makeatother


% Define block styles
\\tikzstyle{decision} = [rectangle, draw, fill=green!20,
text width=20em,  text badly centered, minimum height=2em]
\\tikzstyle{block} = [rectangle, draw, fill=blue!20,
text width=20em, text centered, rounded corners, minimum height=2em]
\\tikzstyle{line} = [draw, -latex']
\\tikzstyle{cloud} = [draw, ellipse,fill=red!20,
minimum height=2em]
\\usepackage{chngcntr}

\\begin{document}

'''
template_node = '''\\begin{{figure}}[H]%
    \\hspace*{{-1in}}
    \\centering
    \\subfloat[]{{{{\includegraphics[width=8cm]{{{}}} }}}}%
    \\qquad
    \\subfloat[]{{{{\includegraphics[width=8cm]{{{}}} }}}}%
\\end{{figure}}
'''
name = "summary_tree.tex"
for path in paths:
    path_ = 'D:/agh/semestr6/pracaInz/program/' + path
    text += '\\section{{ Siec {} }}'.format(path.split('/')[1].split('_'))
    text += "Rozklad stopni w skali logarytmicznej i normalnej"
    text += template_node.format(path_ +'Rozklad_stopni_loglog.pdf', path_ + 'Rozklad_Rozklad_stopni_norm.pdf')
    text += "Sredni czas do huba oraz srednie obciazenie na nodzie"
    text += template_node.format(path_ +'time_to_hub_average.pdf', path_ + 'average_traffic_on_degree.pdf')
    
text += '\\end{document}'
with open('summary/'+name, 'w') as f:
    f.write(text)
