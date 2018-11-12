import glob as g

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
\\section{Wykresy dla u 1 v 4}
	\\subsection{generacja 5}
'''
template_node = '''\\begin{{figure}}[H]%
     \\hspace*{{-1in}}
    \\vspace*{{-1in}}
    \\centering
    \\subfloat[]{{{{\includegraphics[width=8cm]{{{}}} }}}}%
    \\qquad
    \\subfloat[]{{{{\includegraphics[width=8cm]{{{}}} }}}}%
\\end{{figure}}
'''
name = "gen5_u1_v4.tex"
for i in range(0,11):
	
    text += '\\vspace*{{0.5in}}\\subsubsection{{Prawdopodobienstwo {}}}'.format(i/10)
    insert = ''
    if i == 10:
        insert = 'g5_u1_v4/p10'
    else:
        insert = 'g5_u1_v4/p0{}'.format(i)
    
    path = 'D:/agh/semestr6/pracaInz/program/randomWalkDat_t/{}/nodeTime/*.pdf'.format(insert)
    path_num = 'D:/agh/semestr6/pracaInz/program/randomWalkDat_t/{}/trafficNum/*.pdf'.format(insert)
    path_avg = 'D:/agh/semestr6/pracaInz/program/randomWalkDat_t/{}/*.pdf'.format(insert)
    com_path ='D:/agh/semestr6/pracaInz/program/randomWalkDat_t/{}/'.format(insert[:-3])

    files = g.glob(path)

    for i in range(0,len(files),2):
        files[i] = files[i].split('\\')
        files[i]= '/'.join(files[i])
        if i + 1 <len(files):
            files[i+1] = files[i+1].split('\\')
            files[i+1]= '/'.join(files[i+1])
            text += template_node.format(files[i], files[i+1])

    text += '\\vspace*{1in}Numerical traffic on nodes'

    files_num = g.glob(path_num)
    for i in range(0,len(files_num),2):
        files_num[i] = files_num[i].split('\\')
        files_num[i]= '/'.join(files_num[i])
        if i + 1 <len(files_num):
            files_num[i+1] = files_num[i+1].split('\\')
            files_num[i+1]= '/'.join(files_num[i+1])
            text += template_node.format(files_num[i], files_num[i+1])

    text += '\\vspace*{1in}Average'
    avg = g.glob(path_avg)
    avg[0] = avg[0].split('\\')
    avg[0]= '/'.join(avg[0])
    avg[1] = avg[1].split('\\')
    avg[1]= '/'.join(avg[1])
    text += template_node.format(avg[0], avg[1])
text += '''\\vspace*{{1in}}Average
\\begin{{figure}}[H]%
     \\centering
     \\includegraphics[scale=0.6]{{{}comparision.pdf}}
\\end{{figure}}
'''.format(com_path)
text += '\\end{document}'
with open('tex_t/'+name, 'w') as f:
    f.write(text)
