/*
 * Embroidermodder 2.
 *
 * Copyright 2013-2024 The Embroidermodder Team
 * Embroidermodder 2 is Open Source Software, see LICENSE for licensing terms.
 * Read CODE-STANDARDS.txt for advice on altering this file.
 *
 * Command: SNOWFLAKE
 */

#include "../commands.h"

/* NOTE: main() is run every time the command is started.
 *       Use it to reset variables so they are ready to go.
 */
ScriptValue
snowflake_command(ScriptEnv * context)
{
    return script_null;
}

#if 0
//Command: Snowflake

var global = {}; //Required
global.numPoints = 2048; //Default //TODO: min:64 max:8192
global.cx;
global.cy;
global.sx = 0.04; //Default
global.sy = 0.04; //Default
global.numPoints;
global.mode;

//enums
global.mode_NUM_POINTS = 0;
global.mode_XSCALE     = 1;
global.mode_YSCALE     = 2;

//NOTE: main() is run every time the command is started.
//      Use it to reset variables so they are ready to go.
function main()
{
    initCommand();
    clearSelection();
    global.cx = NaN;
    global.cy = NaN;
    global.mode = global.mode_NUM_POINTS;

    addRubber("POLYGON");
    setRubberMode("POLYGON");
    updateSnowflake(global.numPoints, global.sx, global.sy);
    spareRubber("POLYGON");
    endCommand();
}

//NOTE: click() is run only for left clicks.
//      Middle clicks are used for panning.
//      Right clicks bring up the context menu.
function click(x, y)
{
}

//NOTE: move() is optional. It is run only after
//      enableMoveRapidFire() is called. It
//      will be called every time the mouse moves until
//      disableMoveRapidFire() is called.
function move(x, y)
{
}

//NOTE: context() is run when a context menu entry is chosen.
function context(str)
{
    todo("SNOWFLAKE", "context()");
}

//NOTE: prompt() is run when Enter is pressed.
//      appendPromptHistory is automatically called before prompt()
//      is called so calling it is only needed for erroneous input.
//      Any text in the command prompt is sent as an uppercase string.
function prompt(str)
{
}

function updateSnowflake(numPts, xScale, yScale)
{
    var i;
    var t;
    var xx = NaN;
    var yy = NaN;
    var two_pi = 2*Math.PI;

    for(i = 0; i <= numPts; i++)
    {
        t = two_pi/numPts*i; 

//Snowflake Curve with t [0,2pi]

xx = 4/7*Math.sin(20/11-318*t)+
3/13*Math.sin(19/11-317*t)+
3/5*Math.sin(21/16-316*t)+
1/6*Math.sin(17/5-315*t)+
2/9*Math.sin(20/19-314*t)+
5/9*Math.sin(35/9-313*t)+
7/12*Math.sin(9/8-310*t)+
5/16*Math.sin(33/8-309*t)+
5/11*Math.sin(31/11-308*t)+
4/7*Math.sin(3/8-307*t)+
4/11*Math.sin(9/8-306*t)+
7/8*Math.sin(21/11-305*t)+
2/3*Math.sin(55/13-304*t)+
5/9*Math.sin(17/7-303*t)+
3/10*Math.sin(3/13-302*t)+
4/11*Math.sin(60/17-301*t)+
6/11*Math.sin(48/11-300*t)+
9/19*Math.sin(1/6-299*t)+
4/5*Math.sin(19/11-298*t)+
7/13*Math.sin(25/8-297*t)+
7/11*Math.sin(19/7-296*t)+
1/2*Math.sin(1-295*t)+
4/9*Math.sin(24/11-294*t)+
1/3*Math.sin(7/2-291*t)+
6/17*Math.sin(15/13-290*t)+
11/17*Math.sin(32/7-288*t)+
3/8*Math.sin(33/8-287*t)+
4/7*Math.sin(15/7-286*t)+
4/5*Math.sin(48/11-284*t)+
6/7*Math.sin(10/7-283*t)+
6/7*Math.sin(20/11-282*t)+
3/8*Math.sin(11/7-281*t)+
5/7*Math.sin(23/6-280*t)+
1/21*Math.sin(19/12-279*t)+
4/9*Math.sin(1/5-278*t)+
5/8*Math.sin(5/9-276*t)+
9/10*Math.sin(2/3-274*t)+
5/8*Math.sin(5/11-273*t)+
1/6*Math.sin(9/2-272*t)+
12/25*Math.sin(29/12-271*t)+
7/13*Math.sin(59/15-270*t)+
5/7*Math.sin(23/9-269*t)+
3/4*Math.sin(9/2-268*t)+
5/11*Math.sin(37/9-267*t)+
10/11*Math.sin(11/7-266*t)+
1/3*Math.sin(3/7-264*t)+
7/9*Math.sin(33/17-262*t)+
5/8*Math.sin(9/8-261*t)+
5/8*Math.sin(38/13-260*t)+
11/21*Math.sin(36/13-259*t)+
3/11*Math.sin(1/29-258*t)+
8/15*Math.sin(31/8-257*t)+
2/5*Math.sin(3/13-256*t)+
1/2*Math.sin(47/10-255*t)+
1/10*Math.sin(33/10-254*t)+
2/5*Math.sin(1/2-253*t)+
4/7*Math.sin(33/7-252*t)+
6/17*Math.sin(3/8-250*t)+
5/7*Math.sin(25/9-249*t)+
7/9*Math.sin(35/8-248*t)+
2/7*Math.sin(81/20-247*t)+
5/8*Math.sin(25/6-244*t)+
5/16*Math.sin(11/21-243*t)+
11/13*Math.sin(167/42-242*t)+
11/15*Math.sin(18/5-241*t)+
13/14*Math.sin(37/11-240*t)+
1/4*Math.sin(20/9-239*t)+
9/14*Math.sin(52/15-238*t)+
9/14*Math.sin(17/14-237*t)+
6/13*Math.sin(69/17-236*t)+
5/8*Math.sin(74/21-235*t)+
7/15*Math.sin(76/25-234*t)+
10/11*Math.sin(15/8-232*t)+
5/11*Math.sin(5/9-230*t)+
1/8*Math.sin(8/3-229*t)+
5/9*Math.sin(2/7-227*t)+
4/13*Math.sin(32/9-226*t)+
2/3*Math.sin(45/11-225*t)+
1/30*Math.sin(53/15-223*t)+
7/11*Math.sin(4/11-222*t)+
10/19*Math.sin(31/13-221*t)+
Math.sin(13/7-219*t)+
9/14*Math.sin(33/7-216*t)+
2/3*Math.sin(19/9-215*t)+
3/5*Math.sin(27/11-214*t)+
9/11*Math.sin(43/10-210*t)+
5/7*Math.sin(13/8-209*t)+
5/9*Math.sin(21/5-208*t)+
2/7*Math.sin(14/9-206*t)+
9/8*Math.sin(23/7-205*t)+
18/13*Math.sin(11/9-203*t)+
7/4*Math.sin(47/12-201*t)+
10/7*Math.sin(8/9-200*t)+
7/10*Math.sin(6/11-199*t)+
5/3*Math.sin(7/6-198*t)+
19/11*Math.sin(11/6-196*t)+
15/8*Math.sin(9/8-195*t)+
8/17*Math.sin(9/7-192*t)+
8/3*Math.sin(39/10-191*t)+
23/10*Math.sin(2/7-188*t)+
3/4*Math.sin(3/5-187*t)+
7/12*Math.sin(50/11-185*t)+
57/29*Math.sin(4-184*t)+
9/8*Math.sin(6/7-183*t)+
9/7*Math.sin(15/13-182*t)+
5/13*Math.sin(16/7-181*t)+
18/7*Math.sin(5/14-180*t)+
17/9*Math.sin(35/12-179*t)+
5/4*Math.sin(5/7-178*t)+
22/23*Math.sin(3/4-176*t)+
3/8*Math.sin(48/13-175*t)+
15/11*Math.sin(13/11-174*t)+
25/17*Math.sin(23/5-173*t)+
18/11*Math.sin(19/8-172*t)+
11/16*Math.sin(5/3-170*t)+
39/38*Math.sin(15/7-169*t)+
7/6*Math.sin(36/11-166*t)+
15/11*Math.sin(11/6-163*t)+
17/13*Math.sin(3-162*t)+
11/9*Math.sin(20/7-161*t)+
9/7*Math.sin(35/9-160*t)+
7/6*Math.sin(3/2-159*t)+
8/7*Math.sin(9/10-158*t)+
12/25*Math.sin(13/5-156*t)+
6/13*Math.sin(25/13-154*t)+
9/13*Math.sin(7/8-152*t)+
23/10*Math.sin(33/14-151*t)+
8/11*Math.sin(36/11-150*t)+
15/7*Math.sin(26/7-149*t)+
6/5*Math.sin(53/12-148*t)+
14/11*Math.sin(3/2-147*t)+
9/8*Math.sin(4/3-146*t)+
5/8*Math.sin(18/13-145*t)+
15/7*Math.sin(3/8-143*t)+
5/8*Math.sin(5/6-142*t)+
6/7*Math.sin(35/9-139*t)+
16/13*Math.sin(1/2-138*t)+
9/4*Math.sin(7/2-137*t)+
20/9*Math.sin(15/8-135*t)+
11/8*Math.sin(9/4-134*t)+
Math.sin(19/10-133*t)+
22/7*Math.sin(48/11-132*t)+
23/14*Math.sin(1-131*t)+
19/9*Math.sin(27/8-130*t)+
19/5*Math.sin(20/7-129*t)+
18/5*Math.sin(76/25-128*t)+
27/8*Math.sin(4/5-126*t)+
37/8*Math.sin(3/8-125*t)+
62/11*Math.sin(11/3-124*t)+
49/11*Math.sin(7/6-123*t)+
21/22*Math.sin(23/12-122*t)+
223/74*Math.sin(11/3-121*t)+
11/5*Math.sin(19/5-120*t)+
13/4*Math.sin(33/13-119*t)+
27/8*Math.sin(22/5-117*t)+
24/7*Math.sin(13/7-114*t)+
69/17*Math.sin(18/17-113*t)+
10/9*Math.sin(2/7-112*t)+
133/66*Math.sin(12/7-111*t)+
2/5*Math.sin(47/24-110*t)+
13/5*Math.sin(11/6-108*t)+
16/7*Math.sin(39/11-105*t)+
11/5*Math.sin(25/9-104*t)+
151/50*Math.sin(19/7-103*t)+
19/7*Math.sin(12/5-101*t)+
26/7*Math.sin(101/25-99*t)+
43/21*Math.sin(41/14-98*t)+
13/3*Math.sin(31/9-97*t)+
10/13*Math.sin(1-95*t)+
17/7*Math.sin(39/10-93*t)+
145/48*Math.sin(3-92*t)+
37/6*Math.sin(47/13-91*t)+
5/6*Math.sin(36/13-89*t)+
9/4*Math.sin(3/7-87*t)+
48/13*Math.sin(26/17-86*t)+
7/3*Math.sin(28/19-82*t)+
31/6*Math.sin(8/7-81*t)+
36/7*Math.sin(12/7-80*t)+
38/9*Math.sin(25/9-79*t)+
17/2*Math.sin(37/14-76*t)+
16/3*Math.sin(19/20-75*t)+
81/16*Math.sin(4/5-74*t)+
67/10*Math.sin(19/15-73*t)+
40/11*Math.sin(32/11-72*t)+
71/13*Math.sin(21/20-71*t)+
68/15*Math.sin(46/15-70*t)+
52/15*Math.sin(27/10-69*t)+
57/14*Math.sin(7/8-67*t)+
7/4*Math.sin(42/13-66*t)+
39/11*Math.sin(43/21-65*t)+
30/11*Math.sin(33/8-64*t)+
7/5*Math.sin(20/7-63*t)+
4/7*Math.sin(13/14-62*t)+
39/10*Math.sin(16/9-61*t)+
7/6*Math.sin(137/34-59*t)+
16/13*Math.sin(107/27-58*t)+
26/27*Math.sin(17/5-57*t)+
4/3*Math.sin(9/14-56*t)+
46/11*Math.sin(5/3-55*t)+
11/6*Math.sin(13/4-54*t)+
19/4*Math.sin(17/5-53*t)+
19/7*Math.sin(43/11-52*t)+
25/12*Math.sin(30/7-51*t)+
15/7*Math.sin(5/11-50*t)+
53/5*Math.sin(21/13-49*t)+
62/13*Math.sin(67/15-48*t)+
122/9*Math.sin(48/13-47*t)+
20/13*Math.sin(1-46*t)+
7/6*Math.sin(32/7-43*t)+
12/7*Math.sin(13/25-42*t)+
11/17*Math.sin(9/10-40*t)+
11/9*Math.sin(2-39*t)+
4/3*Math.sin(19/7-38*t)+
12/5*Math.sin(47/11-37*t)+
10/7*Math.sin(12/7-36*t)+
108/17*Math.sin(3/4-35*t)+
25/9*Math.sin(19/5-34*t)+
7/13*Math.sin(22/5-33*t)+
9/4*Math.sin(13/11-32*t)+
181/15*Math.sin(25/11-31*t)+
202/11*Math.sin(57/13-29*t)+
2/11*Math.sin(26/7-28*t)+
129/13*Math.sin(38/15-25*t)+
13/6*Math.sin(1/8-24*t)+
77/13*Math.sin(11/8-23*t)+
19/6*Math.sin(15/7-22*t)+
18/7*Math.sin(29/10-21*t)+
9*Math.sin(13/5-18*t)+
342/7*Math.sin(11/6-17*t)+
3/5*Math.sin(49/11-15*t)+
38/3*Math.sin(19/7-14*t)+
994/9*Math.sin(25/8-13*t)+
22/9*Math.sin(49/12-10*t)+
97/9*Math.sin(1/14-8*t)+
559/7*Math.sin(47/14-7*t)+
19/13*Math.sin(5/6-6*t)+
3*Math.sin(57/17-4*t)+
28/5*Math.sin(1-3*t)+
10/3*Math.sin(22/7-2*t)+
1507/3*Math.sin(29/8-t)-
1407/13*Math.sin(5*t+8/11)-
15/2*Math.sin(9*t+2/5)-
1193/9*Math.sin(11*t+28/27)-
209/15*Math.sin(12*t+2/5)-
116/15*Math.sin(16*t+40/39)-
1105/33*Math.sin(19*t+1/3)-
45/13*Math.sin(20*t+7/6)-
91/46*Math.sin(26*t+4/7)-
43/16*Math.sin(27*t+12/11)-
46/13*Math.sin(30*t+14/9)-
29/10*Math.sin(41*t+3/14)-
31/11*Math.sin(44*t+15/14)-
22/7*Math.sin(45*t+10/7)-
7/8*Math.sin(60*t+22/15)-
54/53*Math.sin(68*t+5/4)-
214/15*Math.sin(77*t+5/9)-
54/11*Math.sin(78*t+1/13)-
47/6*Math.sin(83*t+5/11)-
1/2*Math.sin(84*t+8/7)-
2/3*Math.sin(85*t+4/9)-
7/3*Math.sin(88*t+7/6)-
15/4*Math.sin(90*t+1/6)-
35/6*Math.sin(94*t+17/18)-
77/26*Math.sin(96*t+2/7)-
64/11*Math.sin(100*t+34/23)-
13/6*Math.sin(102*t+14/11)-
19/7*Math.sin(106*t+5/6)-
13/6*Math.sin(107*t+10/11)-
42/13*Math.sin(109*t+8/7)-
69/35*Math.sin(115*t+10/21)-
12/7*Math.sin(116*t+17/16)-
8/3*Math.sin(118*t+5/9)-
1/6*Math.sin(127*t+17/12)-
13/7*Math.sin(136*t+8/7)-
7/10*Math.sin(140*t+7/5)-
15/7*Math.sin(141*t+19/14)-
6/11*Math.sin(144*t+5/16)-
3/2*Math.sin(153*t+9/14)-
6/5*Math.sin(155*t+3/10)-
3/8*Math.sin(157*t+10/11)-
20/11*Math.sin(164*t+19/14)-
7/5*Math.sin(165*t+7/6)-
8/13*Math.sin(167*t+20/13)-
7/8*Math.sin(168*t+3/7)-
5/14*Math.sin(171*t+16/13)-
22/7*Math.sin(177*t+3/13)-
23/8*Math.sin(186*t+7/8)-
13/7*Math.sin(189*t+11/9)-
9/5*Math.sin(190*t+32/21)-
27/28*Math.sin(193*t+1)-
5/12*Math.sin(194*t+1/2)-
44/43*Math.sin(197*t+6/5)-
5/11*Math.sin(202*t+1/5)-
8/7*Math.sin(204*t+1/23)-
16/15*Math.sin(207*t+7/10)-
1/2*Math.sin(211*t+2/5)-
5/8*Math.sin(212*t+3/5)-
10/13*Math.sin(213*t+6/5)-
21/16*Math.sin(217*t+4/3)-
11/5*Math.sin(218*t+24/25)-
2/3*Math.sin(220*t+5/9)-
13/10*Math.sin(224*t+7/8)-
17/8*Math.sin(228*t+1/9)-
3/7*Math.sin(231*t+14/9)-
5/12*Math.sin(233*t+9/11)-
3/5*Math.sin(245*t+4/7)-
2/3*Math.sin(246*t+15/11)-
3/8*Math.sin(251*t+4/7)-
2/9*Math.sin(263*t+19/20)-
1/2*Math.sin(265*t+13/11)-
3/8*Math.sin(275*t+3/2)-
17/35*Math.sin(277*t+9/13)-
3/7*Math.sin(285*t+3/11)-
9/10*Math.sin(289*t+25/19)-
4/9*Math.sin(292*t+20/13)-
12/25*Math.sin(293*t+5/4)-
3/5*Math.sin(311*t+9/8)-
33/32*Math.sin(312*t+1/2);

yy = 3/7*Math.sin(24/11-318*t)+
5/12*Math.sin(3-317*t)+
5/14*Math.sin(21/16-316*t)+
9/19*Math.sin(31/9-315*t)+
2/9*Math.sin(13/6-314*t)+
3/5*Math.sin(9/7-312*t)+
2/5*Math.sin(49/12-311*t)+
1/13*Math.sin(30/7-310*t)+
4/13*Math.sin(19/12-309*t)+
1/3*Math.sin(32/7-307*t)+
5/8*Math.sin(22/5-306*t)+
4/11*Math.sin(25/11-305*t)+
8/15*Math.sin(9/8-304*t)+
1/8*Math.sin(35/9-303*t)+
3/5*Math.sin(51/25-302*t)+
2/5*Math.sin(9/8-301*t)+
4/7*Math.sin(2/7-300*t)+
2/7*Math.sin(50/11-299*t)+
3/13*Math.sin(35/8-297*t)+
5/14*Math.sin(14/5-295*t)+
8/13*Math.sin(47/14-294*t)+
2/9*Math.sin(25/8-293*t)+
8/17*Math.sin(136/45-291*t)+
2/7*Math.sin(17/7-290*t)+
3/5*Math.sin(8/7-288*t)+
3/13*Math.sin(19/8-286*t)+
6/11*Math.sin(10/19-285*t)+
9/10*Math.sin(121/40-283*t)+
8/5*Math.sin(21/5-282*t)+
1/10*Math.sin(87/25-281*t)+
7/13*Math.sin(22/7-279*t)+
3/7*Math.sin(8/5-278*t)+
4/5*Math.sin(3/14-277*t)+
7/10*Math.sin(19/13-276*t)+
1/5*Math.sin(6/13-274*t)+
7/10*Math.sin(20/9-273*t)+
1/3*Math.sin(9/4-272*t)+
4/13*Math.sin(47/11-271*t)+
18/17*Math.sin(22/7-269*t)+
1/7*Math.sin(31/9-268*t)+
7/10*Math.sin(43/17-267*t)+
8/11*Math.sin(24/7-266*t)+
5/8*Math.sin(13/6-264*t)+
9/10*Math.sin(17/13-262*t)+
4/11*Math.sin(31/8-261*t)+
1/5*Math.sin(66/19-260*t)+
1/10*Math.sin(23/5-259*t)+
3/10*Math.sin(66/19-255*t)+
1/8*Math.sin(6/7-253*t)+
9/13*Math.sin(16/5-252*t)+
3/7*Math.sin(8/9-251*t)+
4/11*Math.sin(30/13-250*t)+
7/11*Math.sin(66/19-247*t)+
1/19*Math.sin(2-246*t)+
1/4*Math.sin(16/7-245*t)+
8/17*Math.sin(41/10-244*t)+
15/16*Math.sin(2/11-240*t)+
5/7*Math.sin(19/18-239*t)+
1/6*Math.sin(5/12-238*t)+
5/11*Math.sin(16/17-236*t)+
3/10*Math.sin(25/12-235*t)+
8/17*Math.sin(16/7-233*t)+
5/8*Math.sin(47/12-231*t)+
9/11*Math.sin(11/8-230*t)+
3/11*Math.sin(33/7-229*t)+
9/10*Math.sin(20/7-226*t)+
4/9*Math.sin(39/14-225*t)+
4/9*Math.sin(10/9-224*t)+
6/7*Math.sin(19/13-222*t)+
7/9*Math.sin(29/7-221*t)+
8/11*Math.sin(33/8-220*t)+
16/9*Math.sin(2/7-219*t)+
25/14*Math.sin(1/8-218*t)+
8/11*Math.sin(5/9-217*t)+
9/11*Math.sin(11/10-216*t)+
21/13*Math.sin(27/7-215*t)+
3/7*Math.sin(1/12-213*t)+
13/9*Math.sin(15/16-212*t)+
23/8*Math.sin(1/8-210*t)+
Math.sin(32/11-209*t)+
9/13*Math.sin(1/9-208*t)+
7/9*Math.sin(33/10-206*t)+
2/3*Math.sin(9/4-205*t)+
3/4*Math.sin(1/2-204*t)+
3/13*Math.sin(11/17-203*t)+
3/7*Math.sin(31/12-202*t)+
19/12*Math.sin(17/8-201*t)+
7/8*Math.sin(75/19-200*t)+
6/5*Math.sin(21/10-198*t)+
3/2*Math.sin(7/5-194*t)+
28/27*Math.sin(3/2-193*t)+
4/9*Math.sin(16/5-192*t)+
22/13*Math.sin(13/6-189*t)+
18/11*Math.sin(19/10-188*t)+
Math.sin(7/6-187*t)+
16/7*Math.sin(13/11-186*t)+
9/5*Math.sin(11/9-184*t)+
16/11*Math.sin(2/5-183*t)+
10/13*Math.sin(10/3-182*t)+
9/7*Math.sin(38/9-181*t)+
45/13*Math.sin(8/9-180*t)+
7/9*Math.sin(35/8-179*t)+
2/3*Math.sin(35/8-176*t)+
10/7*Math.sin(6/19-175*t)+
40/13*Math.sin(15/7-174*t)+
20/13*Math.sin(1/2-173*t)+
3/11*Math.sin(20/7-171*t)+
17/16*Math.sin(50/11-169*t)+
2/9*Math.sin(1/31-168*t)+
4/9*Math.sin(7/2-165*t)+
1/12*Math.sin(26/17-164*t)+
21/22*Math.sin(27/26-163*t)+
13/12*Math.sin(17/8-162*t)+
19/14*Math.sin(39/10-160*t)+
18/11*Math.sin(5/7-159*t)+
3/5*Math.sin(15/14-158*t)+
11/9*Math.sin(35/8-157*t)+
5/8*Math.sin(30/7-156*t)+
3/2*Math.sin(28/11-155*t)+
4/5*Math.sin(5/11-151*t)+
25/19*Math.sin(11/10-150*t)+
10/11*Math.sin(11/14-148*t)+
13/9*Math.sin(7/4-147*t)+
7/13*Math.sin(19/6-146*t)+
1/5*Math.sin(37/14-145*t)+
11/8*Math.sin(42/13-144*t)+
20/11*Math.sin(32/9-143*t)+
2/3*Math.sin(22/5-141*t)+
10/11*Math.sin(9/7-140*t)+
8/7*Math.sin(23/9-138*t)+
5/2*Math.sin(9/19-137*t)+
7/5*Math.sin(193/48-136*t)+
5/8*Math.sin(67/66-135*t)+
8/7*Math.sin(7/15-134*t)+
13/6*Math.sin(13/7-133*t)+
19/7*Math.sin(16/5-132*t)+
16/7*Math.sin(39/11-131*t)+
28/17*Math.sin(69/35-130*t)+
84/17*Math.sin(7/8-129*t)+
114/23*Math.sin(10/9-128*t)+
29/11*Math.sin(1/7-127*t)+
63/10*Math.sin(65/32-124*t)+
74/17*Math.sin(37/16-121*t)+
31/16*Math.sin(35/11-120*t)+
19/5*Math.sin(23/12-119*t)+
82/27*Math.sin(27/7-118*t)+
49/11*Math.sin(8/3-117*t)+
29/14*Math.sin(63/16-116*t)+
9/13*Math.sin(35/8-114*t)+
29/19*Math.sin(5/4-113*t)+
13/7*Math.sin(20/7-112*t)+
9/7*Math.sin(11/23-111*t)+
19/8*Math.sin(27/26-110*t)+
Math.sin(4/7-109*t)+
119/40*Math.sin(22/5-108*t)+
7/5*Math.sin(47/46-107*t)+
5/3*Math.sin(1/6-106*t)+
2*Math.sin(14/5-105*t)+
7/3*Math.sin(10/3-104*t)+
3/2*Math.sin(15/4-103*t)+
19/11*Math.sin(3/4-102*t)+
74/17*Math.sin(13/10-99*t)+
98/33*Math.sin(26/11-98*t)+
36/11*Math.sin(13/3-97*t)+
43/12*Math.sin(26/25-96*t)+
13/2*Math.sin(3/13-95*t)+
6/7*Math.sin(24/7-94*t)+
16/5*Math.sin(6/5-93*t)+
5/7*Math.sin(9/14-92*t)+
55/12*Math.sin(27/14-90*t)+
15/11*Math.sin(14/3-88*t)+
7/3*Math.sin(7/10-87*t)+
11/4*Math.sin(2/9-86*t)+
13/4*Math.sin(35/12-84*t)+
26/9*Math.sin(38/9-83*t)+
7/2*Math.sin(5/7-82*t)+
31/8*Math.sin(27/8-78*t)+
91/6*Math.sin(35/8-77*t)+
37/5*Math.sin(7/10-76*t)+
70/13*Math.sin(17/11-73*t)+
76/25*Math.sin(56/19-70*t)+
19/8*Math.sin(17/8-68*t)+
59/13*Math.sin(42/17-67*t)+
28/17*Math.sin(49/13-64*t)+
9/7*Math.sin(79/17-63*t)+
1/8*Math.sin(7/11-62*t)+
39/8*Math.sin(49/15-61*t)+
53/18*Math.sin(33/8-59*t)+
9/7*Math.sin(41/9-58*t)+
8/7*Math.sin(65/14-57*t)+
10/11*Math.sin(16/7-56*t)+
68/13*Math.sin(42/13-55*t)+
21/10*Math.sin(7/8-54*t)+
6/7*Math.sin(41/14-53*t)+
31/11*Math.sin(55/12-51*t)+
59/17*Math.sin(27/7-50*t)+
124/9*Math.sin(37/11-49*t)+
24/11*Math.sin(3/5-48*t)+
65/6*Math.sin(12/5-47*t)+
11/7*Math.sin(49/11-45*t)+
13/25*Math.sin(11/13-42*t)+
7/4*Math.sin(5/8-40*t)+
43/42*Math.sin(2/5-39*t)+
20/9*Math.sin(4/7-38*t)+
19/8*Math.sin(4/11-37*t)+
5/4*Math.sin(15/4-36*t)+
1/5*Math.sin(11/13-34*t)+
12/7*Math.sin(23/5-32*t)+
409/34*Math.sin(39/10-31*t)+
10/7*Math.sin(5/2-30*t)+
180/11*Math.sin(3-29*t)+
23/8*Math.sin(53/12-26*t)+
71/8*Math.sin(56/13-25*t)+
12/5*Math.sin(10/21-24*t)+
10/3*Math.sin(34/9-22*t)+
27/16*Math.sin(12/11-21*t)+
49/6*Math.sin(13/7-20*t)+
69/2*Math.sin(19/14-19*t)+
475/9*Math.sin(3/10-17*t)+
68/13*Math.sin(57/28-16*t)+
40/17*Math.sin(1/6-15*t)+
77/13*Math.sin(29/11-12*t)+
4954/39*Math.sin(15/4-11*t)+
1075/11*Math.sin(4-5*t)+
191/24*Math.sin(5/4-4*t)+
84/17*Math.sin(2/7-3*t)-
12/5*Math.sin(74*t)-
4/5*Math.sin(166*t)-
1523/3*Math.sin(t+12/11)-
25/3*Math.sin(2*t+17/18)-
13/8*Math.sin(6*t+1/9)-
5333/62*Math.sin(7*t+9/7)-
56/9*Math.sin(8*t+5/12)-
65/8*Math.sin(9*t+2/5)-
106/9*Math.sin(10*t+1/8)-
1006/9*Math.sin(13*t+11/7)-
67/8*Math.sin(14*t+6/5)-
25/8*Math.sin(18*t+15/11)-
40/11*Math.sin(23*t+1/16)-
4/7*Math.sin(27*t+6/5)-
41/8*Math.sin(28*t+7/12)-
8/5*Math.sin(33*t+5/6)-
137/17*Math.sin(35*t+4/5)-
29/12*Math.sin(41*t+22/15)-
25/9*Math.sin(43*t+6/7)-
12/25*Math.sin(44*t+16/11)-
31/6*Math.sin(46*t+4/3)-
19/5*Math.sin(52*t+16/13)-
19/11*Math.sin(60*t+8/17)-
16/7*Math.sin(65*t+6/13)-
25/12*Math.sin(66*t+11/13)-
8/9*Math.sin(69*t+4/11)-
25/7*Math.sin(71*t+7/5)-
11/10*Math.sin(72*t+3/2)-
14/5*Math.sin(75*t+7/9)-
107/14*Math.sin(79*t+3/4)-
67/8*Math.sin(80*t+2/11)-
161/27*Math.sin(81*t+5/11)-
55/18*Math.sin(85*t+3/7)-
161/40*Math.sin(89*t+1/21)-
32/7*Math.sin(91*t+38/25)-
Math.sin(100*t+19/20)-
27/5*Math.sin(101*t+2/13)-
26/9*Math.sin(115*t+1/44)-
17/11*Math.sin(122*t+1/16)-
87/22*Math.sin(123*t+2/3)-
37/8*Math.sin(125*t+9/11)-
10/7*Math.sin(126*t+8/7)-
7/8*Math.sin(139*t+3/5)-
3/7*Math.sin(142*t+5/6)-
71/36*Math.sin(149*t+5/16)-
7/6*Math.sin(152*t+1/9)-
63/25*Math.sin(153*t+29/19)-
27/20*Math.sin(154*t+8/15)-
8/15*Math.sin(161*t+12/13)-
5/3*Math.sin(167*t+13/10)-
17/25*Math.sin(170*t+3/5)-
10/9*Math.sin(172*t+3/8)-
5/7*Math.sin(177*t+5/8)-
1/2*Math.sin(178*t+7/6)-
34/13*Math.sin(185*t+5/8)-
11/13*Math.sin(190*t+38/39)-
25/19*Math.sin(191*t+11/8)-
11/12*Math.sin(195*t+18/19)-
51/26*Math.sin(196*t+2/7)-
14/9*Math.sin(197*t+4/11)-
19/12*Math.sin(199*t+1)-
19/11*Math.sin(207*t+11/8)-
6/11*Math.sin(211*t+1/20)-
11/7*Math.sin(214*t+1/14)-
7/13*Math.sin(223*t+8/11)-
3/5*Math.sin(227*t+12/13)-
4/5*Math.sin(228*t+29/19)-
11/10*Math.sin(232*t+2/7)-
1/6*Math.sin(234*t+7/11)-
Math.sin(237*t+60/59)-
5/11*Math.sin(241*t+7/8)-
1/2*Math.sin(242*t+8/7)-
7/15*Math.sin(243*t+15/16)-
5/8*Math.sin(248*t+2/3)-
1/3*Math.sin(249*t+4/11)-
2/3*Math.sin(254*t+8/7)-
10/19*Math.sin(256*t+14/11)-
4/9*Math.sin(257*t+8/11)-
3/4*Math.sin(258*t+3/7)-
Math.sin(263*t+2/7)-
3/10*Math.sin(265*t+1/28)-
1/2*Math.sin(270*t+1)-
12/13*Math.sin(275*t+5/8)-
1/4*Math.sin(280*t+16/13)-
1/10*Math.sin(284*t+5/8)-
13/25*Math.sin(287*t+3/7)-
9/13*Math.sin(289*t+3/5)-
22/23*Math.sin(292*t+17/13)-
9/11*Math.sin(296*t+17/11)-
3/7*Math.sin(298*t+12/11)-
5/6*Math.sin(308*t+1/2)-
7/15*Math.sin(313*t+1/3);

        setRubberPoint("POLYGON_POINT_" + i.toString(), xx*xScale, yy*yScale);
    }

    setRubberText("POLYGON_NUM_POINTS", numPts.toString());
}
[Menu]
Name=Draw
Position=100

[ToolBar]
Name=Draw
Position=100

[Tips]
ToolTip=&Snowflake
StatusTip=Creates a snowflake:  SNOWFLAKE

[Prompt]
Alias=SNOWFLAKE
#endif