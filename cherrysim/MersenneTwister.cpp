////////////////////////////////////////////////////////////////////////////////
//MIT License
//
//Copyright(c) 2016 Jakob "Brotcrunsher" Schaal
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
#include "MersenneTwister.h"
#include <cmath>
#include <iostream>
#include "Exceptions.h"

void MersenneTwister::twistIteration(uint32_t i)
{
	uint32_t x = (m_mt[i] & MASK_UPPER) + (m_mt[(i + 1) % N] & MASK_LOWER);

	uint32_t xA = x >> 1;

	if (x & 1)
	{
		xA ^= A;
	}

	m_mt[i] = m_mt[(i + M) % N] ^ xA;
}

void MersenneTwister::twist()
{
	for (uint32_t i = 0; i < N; i++)
	{
		twistIteration(i);
	}
	m_index = 0;
}

MersenneTwister::MersenneTwister()
{
}

MersenneTwister::MersenneTwister(uint32_t seed)
{
	setSeed(seed);
}

void MersenneTwister::setSeed(uint32_t seed)
{
	seed += MersenneTwister::seedOffset;
	m_seed = seed;
	m_mt[0] = seed;

	for (uint32_t i = 1; i < N; i++)
	{
		m_mt[i] = (F * (m_mt[i - 1] ^ (m_mt[i - 1] >> 30)) + i);
	}
	m_index = N;

	m_mt[  0] ^= 672634238;
	m_mt[  1] ^= 1609494099;
	m_mt[  2] ^= 2779317590;
	m_mt[  3] ^= 3204985356;
	m_mt[  4] ^= 838190135;
	m_mt[  5] ^= 2691384404;
	m_mt[  6] ^= 2116979308;
	m_mt[  7] ^= 3429999666;
	m_mt[  8] ^= 1280940441;
	m_mt[  9] ^= 2890787666;
	m_mt[ 10] ^= 1147623111;
	m_mt[ 11] ^= 4037157106;
	m_mt[ 12] ^= 2290224050;
	m_mt[ 13] ^= 24647557;
	m_mt[ 14] ^= 13803608;
	m_mt[ 15] ^= 4105002112;
	m_mt[ 16] ^= 2021603870;
	m_mt[ 17] ^= 3511214032;
	m_mt[ 18] ^= 1278104151;
	m_mt[ 19] ^= 769414856;
	m_mt[ 20] ^= 3311822165;
	m_mt[ 21] ^= 4168288515;
	m_mt[ 22] ^= 1638513030;
	m_mt[ 23] ^= 3016527357;
	m_mt[ 24] ^= 144554240;
	m_mt[ 25] ^= 3990807683;
	m_mt[ 26] ^= 1904622019;
	m_mt[ 27] ^= 3248779487;
	m_mt[ 28] ^= 2043240028;
	m_mt[ 29] ^= 3772488333;
	m_mt[ 30] ^= 3352964819;
	m_mt[ 31] ^= 1134512526;
	m_mt[ 32] ^= 1237677975;
	m_mt[ 33] ^= 4231545244;
	m_mt[ 34] ^= 3362141766;
	m_mt[ 35] ^= 3899708015;
	m_mt[ 36] ^= 1489924363;
	m_mt[ 37] ^= 4167685998;
	m_mt[ 38] ^= 2448732350;
	m_mt[ 39] ^= 407322862;
	m_mt[ 40] ^= 2103775079;
	m_mt[ 41] ^= 1015549210;
	m_mt[ 42] ^= 1874864959;
	m_mt[ 43] ^= 3906516351;
	m_mt[ 44] ^= 1687098481;
	m_mt[ 45] ^= 3459088285;
	m_mt[ 46] ^= 3005961649;
	m_mt[ 47] ^= 3682707516;
	m_mt[ 48] ^= 1247391623;
	m_mt[ 49] ^= 740838789;
	m_mt[ 50] ^= 4090016027;
	m_mt[ 51] ^= 3307242449;
	m_mt[ 52] ^= 902366475;
	m_mt[ 53] ^= 2313482326;
	m_mt[ 54] ^= 261011998;
	m_mt[ 55] ^= 2235308252;
	m_mt[ 56] ^= 588788932;
	m_mt[ 57] ^= 3279538348;
	m_mt[ 58] ^= 2052200626;
	m_mt[ 59] ^= 2947564247;
	m_mt[ 60] ^= 1341890013;
	m_mt[ 61] ^= 3116103077;
	m_mt[ 62] ^= 1332842004;
	m_mt[ 63] ^= 1115014808;
	m_mt[ 64] ^= 33648976;
	m_mt[ 65] ^= 1653053104;
	m_mt[ 66] ^= 3551254162;
	m_mt[ 67] ^= 2255229287;
	m_mt[ 68] ^= 2643013933;
	m_mt[ 69] ^= 2871566501;
	m_mt[ 70] ^= 621013183;
	m_mt[ 71] ^= 2635580269;
	m_mt[ 72] ^= 3226359674;
	m_mt[ 73] ^= 3456062978;
	m_mt[ 74] ^= 4007611342;
	m_mt[ 75] ^= 376568295;
	m_mt[ 76] ^= 2265792632;
	m_mt[ 77] ^= 1393135231;
	m_mt[ 78] ^= 3703756988;
	m_mt[ 79] ^= 1882304996;
	m_mt[ 80] ^= 1138990925;
	m_mt[ 81] ^= 3551258203;
	m_mt[ 82] ^= 2600954228;
	m_mt[ 83] ^= 3567660124;
	m_mt[ 84] ^= 4040582200;
	m_mt[ 85] ^= 3499581787;
	m_mt[ 86] ^= 3327265937;
	m_mt[ 87] ^= 3979661575;
	m_mt[ 88] ^= 2345160448;
	m_mt[ 89] ^= 3071502190;
	m_mt[ 90] ^= 1245565738;
	m_mt[ 91] ^= 1319506276;
	m_mt[ 92] ^= 3762574886;
	m_mt[ 93] ^= 2436915921;
	m_mt[ 94] ^= 3010043992;
	m_mt[ 95] ^= 1240443115;
	m_mt[ 96] ^= 2659820648;
	m_mt[ 97] ^= 2254892900;
	m_mt[ 98] ^= 4167900854;
	m_mt[ 99] ^= 1816397102;
	m_mt[100] ^= 2359231906;
	m_mt[101] ^= 397778543;
	m_mt[102] ^= 721107959;
	m_mt[103] ^= 1728908719;
	m_mt[104] ^= 949849629;
	m_mt[105] ^= 1129969479;
	m_mt[106] ^= 528572276;
	m_mt[107] ^= 2610015737;
	m_mt[108] ^= 1535726490;
	m_mt[109] ^= 4032629080;
	m_mt[110] ^= 1883620890;
	m_mt[111] ^= 265853625;
	m_mt[112] ^= 3533259529;
	m_mt[113] ^= 2507392505;
	m_mt[114] ^= 1481989952;
	m_mt[115] ^= 2031042920;
	m_mt[116] ^= 2654051286;
	m_mt[117] ^= 3308681666;
	m_mt[118] ^= 3455152732;
	m_mt[119] ^= 5140830;
	m_mt[120] ^= 244518831;
	m_mt[121] ^= 3511573044;
	m_mt[122] ^= 1656367068;
	m_mt[123] ^= 2845686404;
	m_mt[124] ^= 4116375051;
	m_mt[125] ^= 2481831962;
	m_mt[126] ^= 2309652300;
	m_mt[127] ^= 1889825287;
	m_mt[128] ^= 3319971087;
	m_mt[129] ^= 3010830558;
	m_mt[130] ^= 2086597716;
	m_mt[131] ^= 1007164305;
	m_mt[132] ^= 3803839512;
	m_mt[133] ^= 509295619;
	m_mt[134] ^= 2741848910;
	m_mt[135] ^= 4174329513;
	m_mt[136] ^= 2897777268;
	m_mt[137] ^= 576654320;
	m_mt[138] ^= 1007337126;
	m_mt[139] ^= 3232504552;
	m_mt[140] ^= 3938219489;
	m_mt[141] ^= 3314120077;
	m_mt[142] ^= 3475323905;
	m_mt[143] ^= 2421309533;
	m_mt[144] ^= 2849636848;
	m_mt[145] ^= 3119836403;
	m_mt[146] ^= 3228393456;
	m_mt[147] ^= 3984998330;
	m_mt[148] ^= 3940368561;
	m_mt[149] ^= 744721622;
	m_mt[150] ^= 2229442478;
	m_mt[151] ^= 1904470006;
	m_mt[152] ^= 1551204711;
	m_mt[153] ^= 1538244139;
	m_mt[154] ^= 3892996979;
	m_mt[155] ^= 4286866343;
	m_mt[156] ^= 4144000631;
	m_mt[157] ^= 4212937871;
	m_mt[158] ^= 1161238942;
	m_mt[159] ^= 3480538608;
	m_mt[160] ^= 1856142260;
	m_mt[161] ^= 934836694;
	m_mt[162] ^= 327345062;
	m_mt[163] ^= 2318552502;
	m_mt[164] ^= 3580781935;
	m_mt[165] ^= 2253415315;
	m_mt[166] ^= 3855463716;
	m_mt[167] ^= 1765083472;
	m_mt[168] ^= 1048986624;
	m_mt[169] ^= 491274051;
	m_mt[170] ^= 2410499764;
	m_mt[171] ^= 3375838253;
	m_mt[172] ^= 1099022061;
	m_mt[173] ^= 3290057555;
	m_mt[174] ^= 2050666730;
	m_mt[175] ^= 862674319;
	m_mt[176] ^= 2171227824;
	m_mt[177] ^= 3912272579;
	m_mt[178] ^= 1948166917;
	m_mt[179] ^= 2728003724;
	m_mt[180] ^= 1863312708;
	m_mt[181] ^= 3606335301;
	m_mt[182] ^= 1900549856;
	m_mt[183] ^= 4261292173;
	m_mt[184] ^= 3890402684;
	m_mt[185] ^= 1955745539;
	m_mt[186] ^= 254551935;
	m_mt[187] ^= 1444718075;
	m_mt[188] ^= 1263523706;
	m_mt[189] ^= 276114127;
	m_mt[190] ^= 1170319099;
	m_mt[191] ^= 3262275447;
	m_mt[192] ^= 3534752945;
	m_mt[193] ^= 3377850662;
	m_mt[194] ^= 1083908285;
	m_mt[195] ^= 4029375413;
	m_mt[196] ^= 52207561;
	m_mt[197] ^= 3579902302;
	m_mt[198] ^= 581852646;
	m_mt[199] ^= 2943959702;
	m_mt[200] ^= 2303040175;
	m_mt[201] ^= 2797919932;
	m_mt[202] ^= 1917410872;
	m_mt[203] ^= 583548913;
	m_mt[204] ^= 2898289129;
	m_mt[205] ^= 4209660503;
	m_mt[206] ^= 3239764197;
	m_mt[207] ^= 2565231262;
	m_mt[208] ^= 1160105471;
	m_mt[209] ^= 887632364;
	m_mt[210] ^= 568809649;
	m_mt[211] ^= 871459772;
	m_mt[212] ^= 1091169404;
	m_mt[213] ^= 2829763662;
	m_mt[214] ^= 1595275561;
	m_mt[215] ^= 431325312;
	m_mt[216] ^= 2529569512;
	m_mt[217] ^= 2879100234;
	m_mt[218] ^= 104038946;
	m_mt[219] ^= 612027151;
	m_mt[220] ^= 373095787;
	m_mt[221] ^= 2597703070;
	m_mt[222] ^= 3184380971;
	m_mt[223] ^= 2152293118;
	m_mt[224] ^= 2361005963;
	m_mt[225] ^= 3334197117;
	m_mt[226] ^= 1017697841;
	m_mt[227] ^= 3663856658;
	m_mt[228] ^= 922279938;
	m_mt[229] ^= 3586414705;
	m_mt[230] ^= 3223883286;
	m_mt[231] ^= 86106339;
	m_mt[232] ^= 2353078382;
	m_mt[233] ^= 3432569963;
	m_mt[234] ^= 15540499;
	m_mt[235] ^= 1026897506;
	m_mt[236] ^= 1560305012;
	m_mt[237] ^= 631626775;
	m_mt[238] ^= 249609430;
	m_mt[239] ^= 1363172204;
	m_mt[240] ^= 1887877998;
	m_mt[241] ^= 2380532695;
	m_mt[242] ^= 3566206664;
	m_mt[243] ^= 277593481;
	m_mt[244] ^= 272396685;
	m_mt[245] ^= 2043630268;
	m_mt[246] ^= 2621335167;
	m_mt[247] ^= 3714894566;
	m_mt[248] ^= 2772009624;
	m_mt[249] ^= 4071122075;
	m_mt[250] ^= 1929453526;
	m_mt[251] ^= 2375292607;
	m_mt[252] ^= 3899690002;
	m_mt[253] ^= 2406755614;
	m_mt[254] ^= 3252688299;
	m_mt[255] ^= 2668674245;
	m_mt[256] ^= 2987724291;
	m_mt[257] ^= 3217367508;
	m_mt[258] ^= 3453899967;
	m_mt[259] ^= 1162180457;
	m_mt[260] ^= 2736467555;
	m_mt[261] ^= 1561867475;
	m_mt[262] ^= 347967469;
	m_mt[263] ^= 618944296;
	m_mt[264] ^= 3402292206;
	m_mt[265] ^= 3147239993;
	m_mt[266] ^= 2028818712;
	m_mt[267] ^= 3015617855;
	m_mt[268] ^= 2275154570;
	m_mt[269] ^= 467030653;
	m_mt[270] ^= 640140855;
	m_mt[271] ^= 348739330;
	m_mt[272] ^= 2916951257;
	m_mt[273] ^= 2641481517;
	m_mt[274] ^= 157286493;
	m_mt[275] ^= 3526124294;
	m_mt[276] ^= 425363489;
	m_mt[277] ^= 3207414546;
	m_mt[278] ^= 2329338764;
	m_mt[279] ^= 307320420;
	m_mt[280] ^= 304170145;
	m_mt[281] ^= 1086802512;
	m_mt[282] ^= 1175331517;
	m_mt[283] ^= 4057704829;
	m_mt[284] ^= 1485530313;
	m_mt[285] ^= 1663478617;
	m_mt[286] ^= 2911198049;
	m_mt[287] ^= 1654143539;
	m_mt[288] ^= 2811883725;
	m_mt[289] ^= 4278303957;
	m_mt[290] ^= 1865793264;
	m_mt[291] ^= 3257337397;
	m_mt[292] ^= 3832367564;
	m_mt[293] ^= 1352876532;
	m_mt[294] ^= 639309575;
	m_mt[295] ^= 2574992333;
	m_mt[296] ^= 1242200758;
	m_mt[297] ^= 3136861677;
	m_mt[298] ^= 138907172;
	m_mt[299] ^= 3304657761;
	m_mt[300] ^= 2264131929;
	m_mt[301] ^= 3057336423;
	m_mt[302] ^= 1732320706;
	m_mt[303] ^= 152871628;
	m_mt[304] ^= 3959438987;
	m_mt[305] ^= 2831547779;
	m_mt[306] ^= 2714255063;
	m_mt[307] ^= 4213707756;
	m_mt[308] ^= 386639893;
	m_mt[309] ^= 3147531160;
	m_mt[310] ^= 1585784421;
	m_mt[311] ^= 2001606804;
	m_mt[312] ^= 2221359547;
	m_mt[313] ^= 216190332;
	m_mt[314] ^= 3684569708;
	m_mt[315] ^= 3383580556;
	m_mt[316] ^= 3475506435;
	m_mt[317] ^= 2676707049;
	m_mt[318] ^= 85939015;
	m_mt[319] ^= 2169759931;
	m_mt[320] ^= 3319192938;
	m_mt[321] ^= 4144191398;
	m_mt[322] ^= 1833034479;
	m_mt[323] ^= 2443439040;
	m_mt[324] ^= 2466883616;
	m_mt[325] ^= 815391646;
	m_mt[326] ^= 4066321191;
	m_mt[327] ^= 3730380868;
	m_mt[328] ^= 568172003;
	m_mt[329] ^= 391489936;
	m_mt[330] ^= 1666226861;
	m_mt[331] ^= 2799112800;
	m_mt[332] ^= 1434014485;
	m_mt[333] ^= 1866047075;
	m_mt[334] ^= 3613722277;
	m_mt[335] ^= 1796107760;
	m_mt[336] ^= 4250948659;
	m_mt[337] ^= 1202635132;
	m_mt[338] ^= 2917846620;
	m_mt[339] ^= 550887238;
	m_mt[340] ^= 4043998586;
	m_mt[341] ^= 3219427069;
	m_mt[342] ^= 2206813681;
	m_mt[343] ^= 2253479412;
	m_mt[344] ^= 3504102336;
	m_mt[345] ^= 2975090903;
	m_mt[346] ^= 3508826905;
	m_mt[347] ^= 3166217132;
	m_mt[348] ^= 2632556471;
	m_mt[349] ^= 1473645144;
	m_mt[350] ^= 1559386454;
	m_mt[351] ^= 4600771;
	m_mt[352] ^= 1284456929;
	m_mt[353] ^= 359537345;
	m_mt[354] ^= 460510142;
	m_mt[355] ^= 2997243064;
	m_mt[356] ^= 4002913704;
	m_mt[357] ^= 872165957;
	m_mt[358] ^= 1750466251;
	m_mt[359] ^= 4056497302;
	m_mt[360] ^= 196967971;
	m_mt[361] ^= 2464901083;
	m_mt[362] ^= 2111956463;
	m_mt[363] ^= 4215666342;
	m_mt[364] ^= 278961255;
	m_mt[365] ^= 1310601338;
	m_mt[366] ^= 327336832;
	m_mt[367] ^= 2383720707;
	m_mt[368] ^= 843353301;
	m_mt[369] ^= 2745768123;
	m_mt[370] ^= 461249781;
	m_mt[371] ^= 3620747494;
	m_mt[372] ^= 1610549668;
	m_mt[373] ^= 903637107;
	m_mt[374] ^= 2727381388;
	m_mt[375] ^= 2357992225;
	m_mt[376] ^= 3023170160;
	m_mt[377] ^= 3470945741;
	m_mt[378] ^= 1415083129;
	m_mt[379] ^= 3086832098;
	m_mt[380] ^= 3800967364;
	m_mt[381] ^= 232819791;
	m_mt[382] ^= 1170848955;
	m_mt[383] ^= 1594985671;
	m_mt[384] ^= 2819678138;
	m_mt[385] ^= 1424457616;
	m_mt[386] ^= 2841781170;
	m_mt[387] ^= 2974630093;
	m_mt[388] ^= 3581663141;
	m_mt[389] ^= 4242937474;
	m_mt[390] ^= 1593073374;
	m_mt[391] ^= 2042776386;
	m_mt[392] ^= 3827698125;
	m_mt[393] ^= 2116173960;
	m_mt[394] ^= 1336427989;
	m_mt[395] ^= 1564289536;
	m_mt[396] ^= 4225814024;
	m_mt[397] ^= 1136267045;
	m_mt[398] ^= 3456820542;
	m_mt[399] ^= 2878649348;
	m_mt[400] ^= 493960520;
	m_mt[401] ^= 2005759220;
	m_mt[402] ^= 2790501022;
	m_mt[403] ^= 3324019398;
	m_mt[404] ^= 2141385535;
	m_mt[405] ^= 3374135692;
	m_mt[406] ^= 2442087325;
	m_mt[407] ^= 3359945900;
	m_mt[408] ^= 568804785;
	m_mt[409] ^= 345235822;
	m_mt[410] ^= 2092616863;
	m_mt[411] ^= 1598445922;
	m_mt[412] ^= 2375625021;
	m_mt[413] ^= 827830969;
	m_mt[414] ^= 4224276653;
	m_mt[415] ^= 3159890185;
	m_mt[416] ^= 3370395383;
	m_mt[417] ^= 192047234;
	m_mt[418] ^= 3517276944;
	m_mt[419] ^= 3517138389;
	m_mt[420] ^= 4185815499;
	m_mt[421] ^= 1015196574;
	m_mt[422] ^= 3935780260;
	m_mt[423] ^= 2511052763;
	m_mt[424] ^= 935068704;
	m_mt[425] ^= 3588394013;
	m_mt[426] ^= 4151700708;
	m_mt[427] ^= 4264638873;
	m_mt[428] ^= 752397921;
	m_mt[429] ^= 2443328418;
	m_mt[430] ^= 886095686;
	m_mt[431] ^= 2036764865;
	m_mt[432] ^= 166293676;
	m_mt[433] ^= 937545517;
	m_mt[434] ^= 2635067505;
	m_mt[435] ^= 1098129685;
	m_mt[436] ^= 1310759210;
	m_mt[437] ^= 1787983610;
	m_mt[438] ^= 3563408192;
	m_mt[439] ^= 3491447959;
	m_mt[440] ^= 2429721844;
	m_mt[441] ^= 561991678;
	m_mt[442] ^= 1953744616;
	m_mt[443] ^= 390285574;
	m_mt[444] ^= 1057924047;
	m_mt[445] ^= 56405996;
	m_mt[446] ^= 438661805;
	m_mt[447] ^= 240630051;
	m_mt[448] ^= 2362866576;
	m_mt[449] ^= 4169423756;
	m_mt[450] ^= 6320912;
	m_mt[451] ^= 1730170472;
	m_mt[452] ^= 3570857224;
	m_mt[453] ^= 3429378215;
	m_mt[454] ^= 2723915438;
	m_mt[455] ^= 900171057;
	m_mt[456] ^= 3064326288;
	m_mt[457] ^= 1044620157;
	m_mt[458] ^= 870463934;
	m_mt[459] ^= 2475158362;
	m_mt[460] ^= 324208483;
	m_mt[461] ^= 3109179278;
	m_mt[462] ^= 4043036084;
	m_mt[463] ^= 1895810124;
	m_mt[464] ^= 2012516380;
	m_mt[465] ^= 2144371193;
	m_mt[466] ^= 2216151046;
	m_mt[467] ^= 18102238;
	m_mt[468] ^= 3313677735;
	m_mt[469] ^= 4168696207;
	m_mt[470] ^= 992940999;
	m_mt[471] ^= 557063635;
	m_mt[472] ^= 1509556210;
	m_mt[473] ^= 331606312;
	m_mt[474] ^= 3384806934;
	m_mt[475] ^= 2129089293;
	m_mt[476] ^= 254737047;
	m_mt[477] ^= 4177637546;
	m_mt[478] ^= 1898756746;
	m_mt[479] ^= 2342504493;
	m_mt[480] ^= 1818053662;
	m_mt[481] ^= 1744025299;
	m_mt[482] ^= 204893902;
	m_mt[483] ^= 1813485694;
	m_mt[484] ^= 3388311616;
	m_mt[485] ^= 154923104;
	m_mt[486] ^= 892023194;
	m_mt[487] ^= 4212555626;
	m_mt[488] ^= 1229364370;
	m_mt[489] ^= 2345408035;
	m_mt[490] ^= 1973454851;
	m_mt[491] ^= 3554535516;
	m_mt[492] ^= 3159526361;
	m_mt[493] ^= 1887525421;
	m_mt[494] ^= 2051252535;
	m_mt[495] ^= 1051895253;
	m_mt[496] ^= 3254963068;
	m_mt[497] ^= 2939896476;
	m_mt[498] ^= 2322496839;
	m_mt[499] ^= 154794250;
	m_mt[500] ^= 1714003610;
	m_mt[501] ^= 911136067;
	m_mt[502] ^= 2073818834;
	m_mt[503] ^= 2825204306;
	m_mt[504] ^= 441935408;
	m_mt[505] ^= 3745790942;
	m_mt[506] ^= 3748340725;
	m_mt[507] ^= 4134665382;
	m_mt[508] ^= 3180079856;
	m_mt[509] ^= 2304027262;
	m_mt[510] ^= 4278262920;
	m_mt[511] ^= 1156524773;
	m_mt[512] ^= 571166691;
	m_mt[513] ^= 1849572101;
	m_mt[514] ^= 3223709439;
	m_mt[515] ^= 2057446888;
	m_mt[516] ^= 3529487836;
	m_mt[517] ^= 568196393;
	m_mt[518] ^= 3517964447;
	m_mt[519] ^= 1609016489;
	m_mt[520] ^= 604769011;
	m_mt[521] ^= 3304154645;
	m_mt[522] ^= 3134481208;
	m_mt[523] ^= 2894590260;
	m_mt[524] ^= 1268937414;
	m_mt[525] ^= 3200354268;
	m_mt[526] ^= 2882374964;
	m_mt[527] ^= 763503910;
	m_mt[528] ^= 1002532750;
	m_mt[529] ^= 1546028981;
	m_mt[530] ^= 3874457646;
	m_mt[531] ^= 3419012548;
	m_mt[532] ^= 1489234739;
	m_mt[533] ^= 1892113388;
	m_mt[534] ^= 2934737236;
	m_mt[535] ^= 1644541084;
	m_mt[536] ^= 2367679915;
	m_mt[537] ^= 1811122208;
	m_mt[538] ^= 2447868534;
	m_mt[539] ^= 2390856516;
	m_mt[540] ^= 384473923;
	m_mt[541] ^= 1608038890;
	m_mt[542] ^= 3785440817;
	m_mt[543] ^= 2948893168;
	m_mt[544] ^= 2535806780;
	m_mt[545] ^= 3768994775;
	m_mt[546] ^= 485327531;
	m_mt[547] ^= 3013367843;
	m_mt[548] ^= 3966187213;
	m_mt[549] ^= 3661463757;
	m_mt[550] ^= 965463125;
	m_mt[551] ^= 3307113911;
	m_mt[552] ^= 2544097907;
	m_mt[553] ^= 3408492006;
	m_mt[554] ^= 3066949772;
	m_mt[555] ^= 3713204572;
	m_mt[556] ^= 1048344740;
	m_mt[557] ^= 3128484274;
	m_mt[558] ^= 1840674461;
	m_mt[559] ^= 2393288804;
	m_mt[560] ^= 3180702400;
	m_mt[561] ^= 1889250175;
	m_mt[562] ^= 3118676051;
	m_mt[563] ^= 4197949330;
	m_mt[564] ^= 1492830015;
	m_mt[565] ^= 2644634731;
	m_mt[566] ^= 2103242895;
	m_mt[567] ^= 1630583029;
	m_mt[568] ^= 2777035439;
	m_mt[569] ^= 3032829421;
	m_mt[570] ^= 2784046191;
	m_mt[571] ^= 1709521622;
	m_mt[572] ^= 1320389287;
	m_mt[573] ^= 3129007426;
	m_mt[574] ^= 3469349656;
	m_mt[575] ^= 1666996901;
	m_mt[576] ^= 1301253525;
	m_mt[577] ^= 2822970719;
	m_mt[578] ^= 2992974115;
	m_mt[579] ^= 500417931;
	m_mt[580] ^= 418687311;
	m_mt[581] ^= 2424089276;
	m_mt[582] ^= 3263046437;
	m_mt[583] ^= 1289280656;
	m_mt[584] ^= 756512395;
	m_mt[585] ^= 1919446947;
	m_mt[586] ^= 3295349912;
	m_mt[587] ^= 3578353188;
	m_mt[588] ^= 3113374393;
	m_mt[589] ^= 3888712186;
	m_mt[590] ^= 1534870770;
	m_mt[591] ^= 648740848;
	m_mt[592] ^= 4023738664;
	m_mt[593] ^= 2612010773;
	m_mt[594] ^= 294661426;
	m_mt[595] ^= 4242177727;
	m_mt[596] ^= 790044633;
	m_mt[597] ^= 1701885341;
	m_mt[598] ^= 1391744989;
	m_mt[599] ^= 1776894080;
	m_mt[600] ^= 1517752733;
	m_mt[601] ^= 3629574978;
	m_mt[602] ^= 2509964073;
	m_mt[603] ^= 771191798;
	m_mt[604] ^= 168416672;
	m_mt[605] ^= 2789847517;
	m_mt[606] ^= 245611490;
	m_mt[607] ^= 2867459840;
	m_mt[608] ^= 12282569;
	m_mt[609] ^= 2275557534;
	m_mt[610] ^= 3497736456;
	m_mt[611] ^= 1786375519;
	m_mt[612] ^= 1005568456;
	m_mt[613] ^= 765074589;
	m_mt[614] ^= 3416220119;
	m_mt[615] ^= 1773657503;
	m_mt[616] ^= 870948719;
	m_mt[617] ^= 2444995732;
	m_mt[618] ^= 2892832961;
	m_mt[619] ^= 434922708;
	m_mt[620] ^= 3943628873;
	m_mt[621] ^= 3003171463;
	m_mt[622] ^= 4035066306;
	m_mt[623] ^= 2215993992;

	//Warmup the MersenneTwister.
	for (uint32_t i = 0; i < N; i++)
	{
		nextU32();
	}
}

double MersenneTwister::nextDouble()
{
	while (true)
	{
		double retVal = (double)nextU32() / (double)0xFFFFFFFF;
		if (retVal != 1.0)
		{
			return retVal;
		}
	}
}

uint32_t MersenneTwister::nextU32(uint32_t min, uint32_t max)
{
	const uint32_t range = max - min + 1;
	return (uint32_t)(nextDouble() * range) + min;
}

double MersenneTwister::nextDouble(double min, double max)
{
	const double range = max - min;
	return nextDouble() * range + min;
}

double MersenneTwister::nextNormal(double mean, double sigma)
{
	double v1, sx;
	do {
		v1 = 2 * nextDouble() - 1;
		double v2 = 2 * nextDouble() - 1;
		sx = v1 * v1 + v2 * v2;
	} while (sx >= 1);
	
	double fx = std::sqrt(-2.0 * std::log(sx) / sx);

	return (fx * v1 * sigma + mean);
}

uint32_t MersenneTwister::nextU32()
{
	if (m_seed == 0)
	{
		SIMEXCEPTION(IllegalStateException);
	}
	if (m_index >= N)
	{
		twist();
	}

	uint32_t x = m_mt[m_index];
	m_index++;

	x ^= (x >> U);
	x ^= (x << S) & B;
	x ^= (x << T) & C;
	x ^= (x >> L);

	return x;
}
