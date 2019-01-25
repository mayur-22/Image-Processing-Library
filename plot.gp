set bar 1.000000 front
set border 2 front lt black linewidth 1.000 dashtype solid
set boxwidth 0.5 absolute
set style fill   solid 0.25 border lt -1
set style circle radius graph 0.02, first 0.00000, 0.00000 
set style ellipse size graph 0.05, 0.03, first 0.00000 angle 0 units xy
unset key
set style textbox transparent margins  1.0,  1.0 border
unset logscale
set pointsize 0.5
set style data boxplot
set xtics border in scale 0,0 nomirror norotate  autojustify
set xtics  norangelimit 
set xtics   ()
set ytics border in scale 1,0.5 nomirror norotate  autojustify
unset paxis 1 tics
unset paxis 2 tics
unset paxis 3 tics
unset paxis 4 tics
unset paxis 5 tics
unset paxis 6 tics
unset paxis 7 tics
set title "Distribution of energy usage of the continents, grouped by type of energy source\n" 
set ylabel "Billion Tons of Oil Equivalent" 
set paxis 1 range [ * : * ] noreverse nowriteback
set paxis 2 range [ * : * ] noreverse nowriteback
set paxis 3 range [ * : * ] noreverse nowriteback
set paxis 4 range [ * : * ] noreverse nowriteback
set paxis 5 range [ * : * ] noreverse nowriteback
set paxis 6 range [ * : * ] noreverse nowriteback
set paxis 7 range [ * : * ] noreverse nowriteback
set colorbox vertical origin screen 0.9, 0.2, 0 size screen 0.05, 0.6, 0 front  noinvert bdefault
x = 0.0
plot 'a.dat' using (1):1, 'a.dat' using (2):2, 'a.dat' using (3):3, 'a.dat' using (4):4