#include "stdafx.h"
#include "Util.h"


char *hexStringToString(char *src, int src_len)
{
	char *dest = NULL;
	src = _strupr(src);
	if (strlen(src) <= 1 || strlen(src) % 2 != 0){
		printf("\n hexStringToString change error !!!\n\n");
		exit(0);
	}
	else
	{
		dest = (char  *)malloc(src_len / 2 + 1);
		memset(dest, 0, src_len / 2 + 1);
		for (int i = 0; i < strlen(src); i = i + 2)
		{
			dest[i / 2] = ((src[i] < 64 ? src[i] - 48 : src[i] - 55) * 16) + (src[i + 1] < 64 ? src[i + 1] - 48 : src[i + 1] - 55);
		}
		//printf("\n");
	}
	return dest;
}

char * stringToHexString(unsigned char *src, int src_len){
	unsigned char *hex_str = NULL;
	char result[3];
	if (src_len > 0){
		hex_str = (unsigned char *)malloc(2 * src_len);
		memset(hex_str, 0, 2 * src_len);
	}
	for (int i = 0; i < src_len; i++){
		sprintf(result, "%02x", src[i]);
		strcat((char *)hex_str, result);
	}
	//printf("\n%s", hex_str);
	return (char *)hex_str;
}


void printfOutResult(unsigned char *  data, int len){
	printf("\n");
	for (int i = 0; i < len; i++){
		printf("%.02x ", data[i] & 0xFF);
		if (i != 0 && (i + 1) % 16 == 0)
			printf("\n");
	}
	printf("\n");
}


unsigned int __ROR4__(unsigned int value, int count) { return _rotr(value, count); }


int unsignedStringCopy(unsigned char *dest, unsigned char * src, int len){
	for (int i = 0; i < len; i++){
		dest[i] = src[i];
	}
	return 0;
}

int test_generate_key_updata1(char * hex_string_key){
	int key_str_len = strlen(hex_string_key) / 2;
	char *init_key_hex = "0123456789ABCDEFFEDCBA9876543210F0E1D2C3";
	int init_key_len = strlen(init_key_hex) / 2;
	char *data = (char *)malloc(1024);
	memset(data, 0, 1024);
	char *key_str = hexStringToString(hex_string_key, strlen(hex_string_key));
	printfOutResult((unsigned char *)key_str, 30);
	char *init_key = hexStringToString(init_key_hex, strlen(init_key_hex));
	int k = key_str_len * 8;
	char   tem[10];
	sprintf_s(tem, "%04x", k);
	printf("tem: %s\n", tem);
	for (int i = 0; i < 4; i++){
		tem[i] = tem[i] - 48;
	}
	printfOutResult((unsigned char *)tem, 4);
	unsignedStringCopy((unsigned char *)data, (unsigned char *)init_key, init_key_len);
	printfOutResult((unsigned char *)data, 92 / 2);
	printf("\n\n");
	unsignedStringCopy((unsigned char *)data + init_key_len, (unsigned char *)tem, 4);
	printfOutResult((unsigned char *)data, 92 / 2);
	unsignedStringCopy((unsigned char *)data + 28, (unsigned char *)key_str, key_str_len);
	printfOutResult((unsigned char *)data, 92);
	char *result = getLastKeyResult_4F1B0(data, data + 28);
	printfOutResult((unsigned char *)result, 92);
	return 0;
}

char * test_gen_middle_data(char *initData){
	char *init = initData;
	int DATA_LEN = 20;
	char *result = (char *)malloc(DATA_LEN + 1);
	memset(result, 0, DATA_LEN + 1);
	int tem = 0;
	for (int i = 0; i < DATA_LEN; i++){
		tem = (init[i] & 0xFF) * 91;
		result[i] = (tem + 62) & 0xFF;
	}
	return result;
}

int test_init_key_data(char *v7, char *v9, int  DATA_LEN, char *r){
	char *init = r;
	strncpy(v7, init, strlen(init));
	for (int i = 0; i < DATA_LEN - 1; i++){
		v9[i] = v7[i] ^ 0x5C;
		v7[i] = v7[i] ^ 0x36;
	}
	return 0;
}

int generateNeedKey(char *inputData){
	char *r = test_gen_middle_data(inputData);
	printf("%s", r);
	int DATA_LEN = 65;
	char *v7 = (char *)malloc(DATA_LEN);
	memset(v7, 0, DATA_LEN);
	char *v9 = (char *)malloc(DATA_LEN);
	memset(v9, 0, DATA_LEN);
	test_init_key_data(v7, v9, DATA_LEN, r);

	printf("\n\nk1:产生过程：\n");
	test_generate_key_updata1(stringToHexString(((unsigned char *)v7), DATA_LEN - 1));
	printf("\n*****************************************");
	printf("\n\nk2:产生过程：\n");
	test_generate_key_updata1(stringToHexString(((unsigned char *)v9), DATA_LEN - 1));
	return 0;
}




char * getLastKeyResult_4F1B0(char * result, char *a2)
{
	char  *v2; // r2@1

	int v8; // r3@3
	int v9; // r2@3
	int v10; // r4@3
	int v11; // r12@3
	int v12; // off@3
	int v13; // r11@3
	int v14; // r1@3
	int v15; // off@3
	int v16; // off@3
	int v17; // r8@3
	int v18; // r7@3
	int v19; // off@3
	int v20; // r2@3
	int v21; // off@3
	int v22; // r4@3
	int v23; // r8@3
	int v24; // r4@3
	int v25; // r3@3
	int v26; // off@3
	int v27; // r4@3
	int v28; // off@3
	int v29; // r6@3
	int v30; // r12@3
	int v31; // off@3
	int v32; // r6@3
	int v33; // off@3
	int v34; // r10@3
	int v35; // r1@3
	int v36; // off@3
	int v37; // r10@3
	int v38; // off@3
	int v39; // r8@3
	int v40; // off@3
	int v41; // r2@3
	int v42; // off@3
	int v43; // r7@3
	int v44; // r10@3
	int v45; // r7@3
	int v46; // r3@3
	int v47; // off@3
	int v48; // r7@3
	int v49; // off@3
	int v50; // r6@3
	int v51; // r4@3
	int v52; // off@3
	int v53; // r12@3
	int v54; // off@3
	int v55; // r7@3
	int v56; // r6@3
	int v57; // r1@3
	int v58; // off@3
	int v59; // r6@3
	int v60; // off@3
	int v61; // r10@3
	int v62; // r2@3
	int v63; // off@3
	int v64; // r10@3
	int v65; // off@3
	int v66; // r8@3
	int v67; // r3@3
	int v68; // off@3
	int v69; // r8@3
	int v70; // off@3
	int v71; // r7@3
	int v72; // off@3
	int v73; // r12@3
	int v74; // off@3
	int v75; // r6@3
	int v76; // r4@3
	int v77; // r1@3
	int v78; // off@3
	int v79; // r4@3
	int v80; // off@3
	int v81; // r6@3
	int v82; // off@3
	int v83; // r2@3
	int v84; // off@3
	int v85; // ST04_4@3
	int v86; // r8@3
	int v87; // off@3
	int v88; // ST08_4@3
	int v89; // r3@3
	int v90; // off@3
	int v91; // r6@3
	int v92; // off@3
	int v93; // off@3
	int v94; // ST30_4@3
	int v95; // r9@3
	int v96; // off@3
	int v97; // r12@3
	int v98; // off@3
	int v99; // off@3
	int v100; // ST2C_4@3
	int v101; // r7@3
	int v102; // off@3
	int v103; // r4@3
	int v104; // r12@3
	int v105; // off@3
	int v106; // r1@3
	int v107; // off@3
	int v108; // r6@3
	int v109; // r12@3
	int v110; // off@3
	int v111; // off@3
	int v112; // r3@3
	int v113; // r9@3
	int v114; // off@3
	int v115; // ST38_4@3
	int v116; // r3@3
	int v117; // off@3
	int v118; // r10@3
	int v119; // off@3
	int v120; // off@3
	int v121; // ST20_4@3
	int v122; // r9@3
	int v123; // off@3
	int v124; // r5@3
	int v125; // off@3
	int v126; // r6@3
	int v127; // r7@3
	int v128; // off@3
	int v129; // r8@3
	int v130; // r1@3
	int v131; // off@3
	int v132; // r2@3
	int v133; // off@3
	int v134; // off@3
	int v135; // ST1C_4@3
	int v136; // ST18_4@3
	int v137; // r12@3
	int v138; // r4@3
	int v139; // off@3
	int v140; // r8@3
	int v141; // off@3
	int v142; // off@3
	int v143; // ST14_4@3
	int v144; // r2@3
	int v145; // off@3
	int v146; // r3@3
	int v147; // off@3
	int v148; // r12@3
	int v149; // r4@3
	int v150; // r12@3
	int v151; // off@3
	int v152; // r6@3
	int v153; // r1@3
	int v154; // off@3
	int v155; // off@3
	int v156; // ST34_4@3
	int v157; // r7@3
	int v158; // r4@3
	int v159; // r6@3
	int v160; // off@3
	int v161; // r4@3
	int v162; // off@3
	int v163; // off@3
	int v164; // ST28_4@3
	int v165; // r2@3
	int v166; // off@3
	int v167; // ST10_4@3
	int v168; // r11@3
	int v169; // r5@3
	int v170; // off@3
	int v171; // r3@3
	int v172; // r2@3
	int v173; // off@3
	int v174; // r12@3
	int v175; // r9@3
	int v176; // r4@3
	int v177; // off@3
	int v178; // ST04_4@3
	int v179; // off@3
	int v180; // ST0C_4@3
	int v181; // r1@3
	int v182; // off@3
	int v183; // r12@3
	int v184; // off@3
	int v185; // r4@3
	int v186; // off@3
	int v187; // r10@3
	int v188; // off@3
	int v189; // off@3
	int v190; // ST24_4@3
	int v191; // r3@3
	int v192; // off@3
	int v193; // r5@3
	int v194; // off@3
	int v195; // r6@3
	int v196; // r9@3
	int v197; // r2@3
	int v198; // off@3
	int v199; // r6@3
	int v200; // off@3
	int v201; // ST08_4@3
	int v202; // r8@3
	int v203; // r1@3
	int v204; // off@3
	int v205; // off@3
	int v206; // r7@3
	int v207; // ST30_4@3
	int v208; // r4@3
	int v209; // r8@3
	int v210; // off@3
	int v211; // r9@3
	int v212; // off@3
	int v213; // r11@3
	int v214; // ST2C_4@3
	int v215; // r6@3
	int v216; // r12@3
	int v217; // r3@3
	int v218; // off@3
	int v219; // r5@3
	int v220; // off@3
	int v221; // r2@3
	int v222; // off@3
	int v223; // r12@3
	int v224; // off@3
	int v225; // r11@3
	int v226; // r1@3
	int v227; // off@3
	int v228; // r6@3
	int v229; // off@3
	int v230; // off@3
	int v231; // ST2C_4@3
	int v232; // r4@3
	int v233; // off@3
	int v234; // r2@3
	int v235; // off@3
	int v236; // r7@3
	int v237; // off@3
	int v238; // ST38_4@3
	int v239; // r8@3
	int v240; // off@3
	int v241; // r10@3
	int v242; // off@3
	int v243; // off@3
	int v244; // ST20_4@3
	int v245; // r9@3
	int v246; // off@3
	int v247; // r11@3
	int v248; // off@3
	int v249; // r5@3
	int v250; // off@3
	int v251; // ST1C_4@3
	int v252; // r10@3
	int v253; // off@3
	int v254; // r4@3
	int v255; // off@3
	int v256; // r6@3
	int v257; // off@3
	int v258; // ST18_4@3
	int v259; // r1@3
	int v260; // off@3
	int v261; // r5@3
	int v262; // off@3
	int v263; // off@3
	int v264; // ST14_4@3
	int v265; // r8@3
	int v266; // off@3
	int v267; // r12@3
	int v268; // r11@3
	int v269; // off@3
	int v270; // r12@3
	int v271; // r5@3
	int v272; // r12@3
	int v273; // off@3
	int v274; // r7@3
	int v275; // off@3
	int v276; // off@3
	int v277; // ST34_4@3
	int v278; // r9@3
	int v279; // off@3
	int v280; // ST28_4@3
	int v281; // r2@3
	int v282; // off@3
	int v283; // r12@3
	int v284; // off@3
	int v285; // off@3
	int v286; // ST10_4@3
	int v287; // r9@3
	int v288; // off@3
	int v289; // r1@3
	int v290; // off@3
	int v291; // r4@3
	int v292; // r2@3
	int v293; // off@3
	int v294; // ST04_4@3
	int v295; // r4@3
	int v296; // off@3
	int v297; // r9@3
	int v298; // off@3
	int v299; // r2@3
	int v300; // r7@3
	int v301; // r2@3
	int v302; // off@3
	int v303; // r6@3
	int v304; // off@3
	int v305; // off@3
	int v306; // ST0C_4@3
	int v307; // r12@3
	int v308; // r4@3
	int v309; // r12@3
	int v310; // off@3
	int v311; // r7@3
	int v312; // off@3
	int v313; // off@3
	int v314; // ST24_4@3
	int v315; // r11@3
	int v316; // r8@3
	int v317; // off@3
	int v318; // r4@3
	int v319; // off@3
	int v320; // off@3
	int v321; // ST08_4@3
	int v322; // r1@3
	int v323; // r9@3
	int v324; // off@3
	int v325; // r4@3
	int v326; // off@3
	int v327; // r2@3
	int v328; // off@3
	int v329; // r1@3
	int v330; // off@3
	int v331; // r12@3
	int v332; // off@3
	int v333; // off@3
	int v334; // r6@3
	int v335; // ST30_4@3
	int v336; // r7@3
	int v337; // r10@3
	int v338; // off@3
	int v339; // r1@3
	int v340; // off@3
	int v341; // r5@3
	int v342; // off@3
	int v343; // r8@3
	int v344; // off@3
	int v345; // r7@3
	int v346; // off@3
	int v347; // r3@3
	int v348; // off@3
	int v349; // ST2C_4@3
	int v350; // r4@3
	int v351; // r5@3
	int v352; // r12@3
	int v353; // r8@3
	int v354; // r11@3
	int v355; // off@3
	int v356; // r5@3
	int v357; // off@3
	int v358; // ST38_4@3
	int v359; // r7@3
	int v360; // off@3
	int v361; // r6@3
	int v362; // r9@3
	int v363; // r8@3
	int v364; // off@3
	int v365; // r4@3
	int v366; // off@3
	int v367; // r11@3
	int v368; // off@3
	int v369; // ST20_4@3
	int v370; // r3@3
	int v371; // off@3
	int v372; // ST1C_4@3
	int v373; // r5@3
	int v374; // r11@3
	int v375; // off@3
	int v376; // r8@3
	int v377; // off@3
	int v378; // r1@3
	int v379; // r5@3
	int v380; // off@3
	int v381; // r3@3
	int v382; // off@3
	int v383; // off@3
	int v384; // ST18_4@3
	int v385; // r12@3
	int v386; // r4@3
	int v387; // r1@3
	int v388; // r12@3
	int v389; // off@3
	int v390; // r7@3
	int v391; // off@3
	int v392; // r5@3
	int v393; // off@3
	int v394; // ST14_4@3
	int v395; // r11@3
	int v396; // r1@3
	int v397; // r4@3
	int v398; // off@3
	int v399; // r1@3
	int v400; // off@3
	int v401; // off@3
	int v402; // ST34_4@3
	int v403; // r10@3
	int v404; // r3@3
	int v405; // off@3
	int v406; // ST28_4@3
	int v407; // r12@3
	int v408; // r6@3
	int v409; // r10@3
	int v410; // off@3
	int v411; // r1@3
	int v412; // off@3
	int v413; // off@3
	int v414; // ST10_4@3
	int v415; // r12@3
	int v416; // off@3
	int v417; // r3@3
	int v418; // off@3
	int v419; // off@3
	int v420; // ST04_4@3
	int v421; // r9@3
	int v422; // r10@3
	int v423; // r8@3
	int v424; // off@3
	int v425; // r9@3
	int v426; // off@3
	int v427; // r5@3
	int v428; // r10@3
	int v429; // r4@3
	int v430; // off@3
	int v431; // ST24_4@3
	int v432; // ST0C_4@3
	int v433; // r6@3
	int v434; // r5@3
	int v435; // r10@3
	int v436; // off@3
	int v437; // r9@3
	int v438; // off@3
	int v439; // off@3
	int v440; // ST24_4@3
	int v441; // r7@3
	int v442; // r3@3
	int v443; // r6@3
	int v444; // off@3
	int v445; // r1@3
	int v446; // off@3
	int v447; // off@3
	int v448; // ST08_4@3
	int v449; // r5@3
	int v450; // r11@3
	int v451; // off@3
	int v452; // r7@3
	int v453; // off@3
	int v454; // r4@3
	int v455; // r2@3
	int v456; // off@3
	int v457; // r8@3
	int v458; // off@3
	int v459; // ST30_4@3
	int v460; // r12@3
	int v461; // off@3
	int v462; // r6@3
	int v463; // r5@3
	int v464; // off@3
	int v465; // ST2C_4@3
	int v466; // r10@3
	int v467; // r2@3
	int v468; // r6@3
	int v469; // off@3
	int v470; // r5@3
	int v471; // off@3
	int v472; // off@3
	int v473; // r8@3
	int v474; // r9@3
	int v475; // off@3
	int v476; // r2@3
	int v477; // off@3
	int v478; // r1@3
	int v479; // off@3
	int v480; // r11@3
	int v481; // ST38_4@3
	int v482; // r10@3
	int v483; // r7@3
	int v484; // r3@3
	int v485; // off@3
	int v486; // r1@3
	int v487; // off@3
	int v488; // r8@3
	int v489; // off@3
	int v490; // ST20_4@3
	int v491; // r2@3
	int v492; // r4@3
	int v493; // off@3
	int v494; // r11@3
	int v495; // off@3
	int v496; // r7@3
	int v497; // off@3
	int v498; // ST1C_4@3
	int v499; // r10@3
	int v500; // off@3
	int v501; // r8@3
	int v502; // off@3
	int v503; // r1@3
	int v504; // off@3
	int v505; // r6@3
	int v506; // r2@3
	int v507; // off@3
	int v508; // ST18_4@3
	int v509; // r5@3
	int v510; // r3@3
	int v511; // off@3
	int v512; // r7@3
	int v513; // off@3
	int v514; // ST14_4@3
	int v515; // r5@3
	int v516; // off@3
	int v517; // r12@3
	int v518; // r4@3
	int v519; // off@3
	int v520; // r12@3
	int v521; // r1@3
	int v522; // r2@3
	int v523; // off@3
	int v524; // r12@3
	int v525; // off@3
	int v526; // r7@3
	int v527; // off@3
	int v528; // r9@3
	int v529; // r3@3
	int v530; // off@3
	int v531; // r12@3
	int v532; // off@3
	int v533; // r6@3
	int v534; // off@3
	int v535; // r5@3
	int v536; // r10@3
	int v537; // off@3
	int v538; // r9@3
	int v539; // off@3
	int v540; // r4@3
	int v541; // r5@3
	int v542; // off@3
	int v543; // off@3
	int v544; // r11@3
	int v545; // ST04_4@3
	int v546; // r7@3
	int v547; // off@3
	int v548; // r4@3
	int v549; // off@3
	int v550; // r2@3
	int v551; // r6@3
	int v552; // off@3
	int v553; // r3@3
	int v554; // r9@3
	int v555; // off@3
	int v556; // r4@3
	int v557; // off@3
	int v558; // r11@3
	int v559; // r3@3
	int v560; // off@3
	int v561; // r10@3
	int v562; // off@3
	int v563; // off@3
	int v564; // r12@3
	int v565; // r4@3
	int v566; // off@3
	int v567; // r11@3
	int v568; // off@3
	int v569; // off@3
	int v570; // r3@3
	int v571; // r9@3
	int v572; // r3@3
	int v573; // off@3
	int v574; // r1@3
	int v575; // r4@3
	int v576; // off@3
	int v577; // r1@3
	int v578; // off@3
	int v579; // r5@3
	int v580; // r6@3
	int v581; // off@3
	int v582; // r3@3
	int v583; // off@3
	int v584; // r7@3
	int v585; // off@3
	int *v586; // r2@3
	int v587; // r10@5
	int v588; // r1@5
	int v589; // r3@5
	int v590; // r4@5 
	int v591; // [sp+3Ch] [bp-6Ch]@3
	char * v592; // [sp+40h] [bp-68h]@2
	int v593; // [sp+44h] [bp-64h]@3
	int v594; // [sp+48h] [bp-60h]@3
	int v595; // [sp+4Ch] [bp-5Ch]@3
	int v596; // [sp+50h] [bp-58h]@3
	int v597; // [sp+54h] [bp-54h]@3
	int v598; // [sp+58h] [bp-50h]@3
	int v599; // [sp+5Ch] [bp-4Ch]@3
	int v600; // [sp+60h] [bp-48h]@3
	int v601; // [sp+64h] [bp-44h]@3
	int v602; // [sp+68h] [bp-40h]@3
	int v603; // [sp+6Ch] [bp-3Ch]@3
	int v604; // [sp+70h] [bp-38h]@3
	int v605; // [sp+74h] [bp-34h]@3
	int v606; // [sp+78h] [bp-30h]@3
	int v607; // [sp+7Ch] [bp-2Ch]@3

	v592 = (char *)malloc(64);
	memset(v592, 0, 64);
	//四个字节每次，高位放低位
	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 4; j++){
			v592[4 * i + j] = a2[4 * i + (3 - j)];
		}
	}


	v593 = *(unsigned int *)(v592 + 4);
	v594 = *(unsigned int *)(v592 + 8);
	v595 = *(unsigned int *)(v592 + 12);
	v596 = *(unsigned int *)(v592 + 16);

	v597 = *(unsigned int *)(v592 + 20);
	v598 = *(unsigned int *)(v592 + 24);
	v599 = *(unsigned int *)(v592 + 28);
	v600 = *(unsigned int *)(v592 + 32);
	v601 = *(unsigned int *)(v592 + 36);
	v602 = *(unsigned int *)(v592 + 40);
	v603 = *(unsigned int *)(v592 + 44);
	v604 = *(unsigned int *)(v592 + 48);
	v605 = *(unsigned int *)(v592 + 52);
	v606 = *(unsigned int *)(v592 + 56);
	v607 = *(unsigned int *)(v592 + 60);

	v8 = *(unsigned int *)(result + 8);
	v9 = *(unsigned int *)(result + 12);
	v10 = *(unsigned int *)(result + 4);
	v12 = __ROR4__(v10, 2);
	v11 = v12;
	v13 = v12 ^ v8;
	int temp_result = *(unsigned int *)(result);
	v15 = __ROR4__(temp_result, 2);
	v14 = v15;
	v16 = __ROR4__(temp_result, 27);
	int kkk = *(unsigned int *)v592 + 1518500249 + *(unsigned int *)(result + 16) + v16;
	v17 = *(unsigned int *)v592 + 1518500249 + *(unsigned int *)(result + 16) + v16 + ((v9 ^ v8) & v10 ^ v9);
	v19 = __ROR4__(v17, 27);
	v18 = v593 + 1518500249 + v9 + (v13 & *(unsigned int *)result ^ v8) + v19;
	v21 = __ROR4__(v17, 2);
	v20 = v21;
	v22 = v17 & (v11 ^ v14) ^ v11;
	v23 = v21 ^ v14;
	v24 = v594 + 1518500249 + v8 + v22;
	v26 = __ROR4__(v18, 2);
	v25 = v26;
	v28 = __ROR4__(v18, 27);
	v27 = v24 + v28;
	v29 = v595 + 1518500249 + v11 + (v23 & v18 ^ v14);
	v31 = __ROR4__(v27, 2);
	v30 = v31;
	v33 = __ROR4__(v27, 27);
	v32 = v29 + v33;
	v34 = v596 + 1518500249 + v14 + ((v25 ^ v20) & v27 ^ v20);
	v36 = __ROR4__(v32, 2);
	v35 = v36;
	v38 = __ROR4__(v32, 27);
	v37 = v34 + v38;
	v40 = __ROR4__(v37, 27);
	v39 = v597 + 1518500249 + v20 + ((v30 ^ v25) & v32 ^ v25) + v40;
	v42 = __ROR4__(v37, 2);
	v41 = v42;
	v43 = (v35 ^ v30) & v37 ^ v30;
	v44 = v42 ^ v35;
	v45 = v598 + 1518500249 + v25 + v43;
	v47 = __ROR4__(v39, 2);
	v46 = v47;
	v49 = __ROR4__(v39, 27);
	v48 = v45 + v49;
	v50 = (v46 ^ v41) & v48 ^ v41;
	v52 = __ROR4__(v48, 27);
	v51 = v599 + 1518500249 + v30 + (v44 & v39 ^ v35) + v52;
	v54 = __ROR4__(v48, 2);
	v53 = v54;
	v55 = v54 ^ v46;
	v56 = v600 + 1518500249 + v35 + v50;
	v58 = __ROR4__(v51, 2);
	v57 = v58;
	v60 = __ROR4__(v51, 27);
	v59 = v56 + v60;
	v61 = v601 + 1518500249 + v41 + (v55 & v51 ^ v46);
	v63 = __ROR4__(v59, 2);
	v62 = v63;
	v65 = __ROR4__(v59, 27);
	v64 = v61 + v65;
	v66 = v602 + 1518500249 + v46 + ((v57 ^ v53) & v59 ^ v53);
	v68 = __ROR4__(v64, 2);
	v67 = v68;
	v70 = __ROR4__(v64, 27);
	v69 = v66 + v70;
	v72 = __ROR4__(v69, 27);
	v71 = v603 + 1518500249 + v53 + ((v62 ^ v57) & v64 ^ v57) + v72;
	v74 = __ROR4__(v69, 2);
	v73 = v74;
	v75 = v74 ^ v67;
	v76 = v604 + 1518500249 + v57 + ((v67 ^ v62) & v69 ^ v62);
	v78 = __ROR4__(v71, 2);
	v77 = v78;
	v80 = __ROR4__(v71, 27);
	v79 = v76 + v80;
	v82 = __ROR4__(v79, 27);
	v81 = v605 + 1518500249 + v62 + (v75 & v71 ^ v67) + v82;
	v84 = __ROR4__(v79, 2);
	v83 = v84;
	v85 = v606 + 1518500249 + v67 + ((v77 ^ v73) & v79 ^ v73);
	v86 = (v84 ^ v77) & v81;
	v87 = __ROR4__(v594 ^ *(unsigned int *)v592 ^ v600 ^ v605, 31);
	v88 = v87;
	v90 = __ROR4__(v81, 2);
	v89 = v90;
	v92 = __ROR4__(v81, 27);
	v91 = v85 + v92;
	v93 = __ROR4__(v595 ^ v593 ^ v601 ^ v606, 31);

	v94 = v93;
	v96 = __ROR4__(v91, 2);
	v95 = v96;
	v98 = __ROR4__(v91, 27);
	v97 = v607 + 1518500249 + v73 + (v86 ^ v77) + v98;
	v99 = __ROR4__(v596 ^ v594 ^ v602 ^ v607, 31);
	v100 = v99;
	v102 = __ROR4__(v97, 2);
	v101 = v102;
	v103 = (v95 ^ v89) & v97 ^ v89;
	v105 = __ROR4__(v97, 27);
	v104 = v88 + 1518500249 + v77 + ((v89 ^ v83) & v91 ^ v83) + v105;
	v107 = __ROR4__(v104, 2);
	v106 = v107;
	v108 = (v101 ^ v95) & v104;
	v110 = __ROR4__(v104, 27);
	v109 = v94 + 1518500249 + v83 + v103 + v110;
	v111 = __ROR4__(v597 ^ v595 ^ v603 ^ v88, 31);
	v591 = v111;
	v112 = v100 + 1518500249 + v89 + (v108 ^ v95);
	v113 = v111 + 1518500249 + v95;
	v114 = __ROR4__(v598 ^ v596 ^ v604 ^ v94, 31);
	v115 = v114;
	v117 = __ROR4__(v109, 27);
	v116 = v112 + v117;
	v119 = __ROR4__(v109, 2);
	v118 = v119;
	v120 = __ROR4__(v599 ^ v597 ^ v605 ^ v100, 31);
	v121 = v120;
	v123 = __ROR4__(v116, 27);
	v122 = v113 + ((v106 ^ v101) & v109 ^ v101) + v123;
	v125 = __ROR4__(v116, 2);
	v124 = v125;
	v126 = v125 ^ v118;
	v128 = __ROR4__(v122, 27);
	v127 = v115 + 1859775393 + v101 + (v118 ^ v106 ^ v116) + v128;
	v129 = v121 + 1859775393 + v106;
	v131 = __ROR4__(v122, 2);
	v130 = v131;
	v133 = __ROR4__(v600 ^ v598 ^ v606 ^ v591, 31);
	v132 = v133;
	v134 = __ROR4__(v601 ^ v599 ^ v607 ^ v115, 31);
	v135 = v132;
	v136 = v134;
	v137 = v134;
	v139 = __ROR4__(v127, 27);
	v138 = v129 + (v126 ^ v122) + v139;
	v141 = __ROR4__(v127, 2);
	v140 = v141;
	v142 = __ROR4__(v602 ^ v600 ^ v88 ^ v121, 31);
	v143 = v142;
	v145 = __ROR4__(v138, 27);
	v144 = v132 + 1859775393 + v118 + (v130 ^ v124 ^ v127) + v145;
	v147 = __ROR4__(v138, 2);
	v146 = v147;
	v148 = v137 + 1859775393 + v124 + (v140 ^ v130 ^ v138);
	v149 = v147 ^ v140;
	v151 = __ROR4__(v144, 27);
	v150 = v148 + v151;
	v152 = v143 + 1859775393 + v130;
	v154 = __ROR4__(v144, 2);
	v153 = v154;
	v155 = __ROR4__(v603 ^ v601 ^ v94 ^ v135, 31);
	v156 = v155;
	v157 = v155 + 1859775393;
	v158 = v152 + (v149 ^ v144);
	v160 = __ROR4__(v150, 2);
	v159 = v160;
	v162 = __ROR4__(v150, 27);
	v161 = v158 + v162;
	v163 = __ROR4__(v604 ^ v602 ^ v100 ^ v136, 31);
	v164 = v163;
	v165 = v163 + 1859775393;
	v166 = __ROR4__(v605 ^ v603 ^ v591 ^ v143, 31);
	v167 = v166;
	v168 = v166;
	v170 = __ROR4__(v161, 27);
	v169 = v157 + v140 + (v153 ^ v146 ^ v150) + v170;
	v171 = v165 + v146;
	v173 = __ROR4__(v161, 2);
	v172 = v173;
	v174 = v171 + (v159 ^ v153 ^ v161);
	v175 = v168 + 1859775393 + v153;
	v176 = v173 ^ v159;
	v177 = __ROR4__(v606 ^ v604 ^ v115 ^ v156, 31);
	v178 = v177;
	v179 = __ROR4__(v607 ^ v605 ^ v121 ^ v164, 31);
	v180 = v179;
	v182 = __ROR4__(v169, 2);
	v181 = v182;
	v184 = __ROR4__(v169, 27);
	v183 = v174 + v184;
	v186 = __ROR4__(v183, 27);
	v185 = v175 + (v176 ^ v169) + v186;
	v188 = __ROR4__(v183, 2);
	v187 = v188;
	v189 = __ROR4__(v88 ^ v606 ^ v135 ^ v167, 31);
	v190 = v189;
	v192 = __ROR4__(v185, 27);
	v191 = v178 + 1859775393 + v159 + (v181 ^ v172 ^ v183) + v192;
	v194 = __ROR4__(v185, 2);
	v193 = v194;
	v195 = v180 + 1859775393 + v172 + (v187 ^ v181 ^ v185);
	v196 = v100 ^ v88 ^ v143;
	v198 = __ROR4__(v94 ^ v607 ^ v136 ^ v178, 31);
	v197 = v198;
	v200 = __ROR4__(v191, 27);
	v199 = v195 + v200;
	v201 = v197;
	v202 = v190 + 1859775393 + v181;
	v204 = __ROR4__(v191, 2);
	v203 = v204;
	v205 = __ROR4__(v196 ^ v180, 31);
	v206 = v591 ^ v94;
	v207 = v205;
	v208 = v205;
	v210 = __ROR4__(v199, 27);
	v209 = v202 + (v193 ^ v187 ^ v191) + v210;
	v212 = __ROR4__(v199, 2);
	v211 = v212;
	v213 = v100;
	v214 = v197 + 1859775393 + v187 + (v203 ^ v193 ^ v199);
	v215 = v115 ^ v213 ^ v164;
	v216 = v208 + 1859775393 + v193 + (v212 ^ v203 ^ v209);
	v218 = __ROR4__(v206 ^ v156 ^ v190, 31);
	v217 = v218;
	v220 = __ROR4__(v209, 2);
	v219 = v220;
	v222 = __ROR4__(v209, 27);
	v221 = v214 + v222;
	v224 = __ROR4__(v214 + v222, 27);
	v223 = v216 + v224;
	v225 = v217 + 1859775393 + v203;
	v227 = __ROR4__(v221, 2);
	v226 = v227;
	v229 = __ROR4__(v215 ^ v201, 31);
	v228 = v229;
	v230 = __ROR4__(v121 ^ v591 ^ v167 ^ v207, 31);
	v231 = v228;
	v591 = v230;
	v233 = __ROR4__(v223, 27);
	v232 = v225 + (v219 ^ v211 ^ v221) + v233;
	v235 = __ROR4__(v223, 2);
	v234 = v235;
	v236 = v235 ^ v226 ^ v232;
	v237 = __ROR4__(v135 ^ v115 ^ v178 ^ v217, 31);
	v238 = v237;
	v240 = __ROR4__(v232, 2);
	v239 = v240;
	v242 = __ROR4__(v232, 27);
	v241 = v228 + 1859775393 + v211 + (v226 ^ v219 ^ v223) + v242;
	v243 = __ROR4__(v136 ^ v121 ^ v180 ^ v228, 31);
	v244 = v243;
	v246 = __ROR4__(v143 ^ v135 ^ v190 ^ v591, 31);
	v245 = v246;
	v248 = __ROR4__(v241, 2);
	v247 = v248;
	v250 = __ROR4__(v241, 27);
	v249 = v591 + 1859775393 + v219 + v236 + v250;
	v251 = v245;
	v253 = __ROR4__(v249, 27);
	v252 = v238 + 1859775393 + v226 + (v239 ^ v234 ^ v241) + v253;
	v255 = __ROR4__(v249, 2);
	v254 = v255;
	v256 = v255 ^ v247;
	v257 = __ROR4__(v156 ^ v136 ^ v201 ^ v238, 31);
	v258 = v257;
	v260 = __ROR4__(v252, 2);
	v259 = v260;
	v262 = __ROR4__(v252, 27);
	v261 = v244 + 1859775393 + v234 + (v247 ^ v239 ^ v249) + v262;
	v263 = __ROR4__(v164 ^ v143 ^ v207 ^ v244, 31);
	v264 = v263;
	v266 = __ROR4__(v261, 27);
	v265 = v245 + 1859775393 + v239 + (v256 ^ v252) + v266;
	v267 = v258 + 1859775393 + v247;
	v269 = __ROR4__(v261, 2);
	v268 = v269;
	v270 = v267 + (v259 ^ v254 ^ v261);
	v271 = v265 | v269;
	v273 = __ROR4__(v265, 27);
	v272 = v270 + v273;
	v275 = __ROR4__(v265, 2);
	v274 = v275;
	v276 = __ROR4__(v167 ^ v156 ^ v217 ^ v245, 31);
	v277 = v276;
	v278 = v276 - 1894007588 + v259 + ((v272 | v274) & v268 | v272 & v274);
	v279 = __ROR4__(v178 ^ v164 ^ v231 ^ v258, 31);
	v280 = v279;
	v282 = __ROR4__(v272, 27);
	v281 = v264 - 1894007588 + v254 + (v271 & v259 | v265 & v268) + v282;
	v284 = __ROR4__(v272, 2);
	v283 = v284;
	v285 = __ROR4__(v180 ^ v167 ^ v591 ^ v264, 31);
	v286 = v285;
	v288 = __ROR4__(v281, 27);
	v287 = v278 + v288;
	v290 = __ROR4__(v281, 2);
	v289 = v290;
	v291 = (v281 | v283) & v274 | v281 & v283;
	v292 = (v287 | v290) & v283 | v287 & v290;
	v293 = __ROR4__(v190 ^ v178 ^ v238 ^ v277, 31);
	v294 = v293;
	v296 = __ROR4__(v287, 27);
	v295 = v280 - 1894007588 + v268 + v291 + v296;
	v298 = __ROR4__(v287, 2);
	v297 = v298;
	v299 = v286 - 1894007588 + v274 + v292;
	v300 = v295 | v298;
	v302 = __ROR4__(v295, 27);
	v301 = v299 + v302;
	v304 = __ROR4__(v295, 2);
	v303 = v304;
	v305 = __ROR4__(v201 ^ v180 ^ v244 ^ v280, 31);
	v306 = v305;
	v307 = v294 - 1894007588 + v283 + (v300 & v289 | v295 & v297);
	v308 = v305;
	v310 = __ROR4__(v301, 27);
	v309 = v307 + v310;
	v312 = __ROR4__(v301, 2);
	v311 = v312;
	v313 = __ROR4__(v207 ^ v190 ^ v251 ^ v286, 31);
	v314 = v313;
	v315 = v313;
	v317 = __ROR4__(v309, 2);
	v316 = v317;
	v319 = __ROR4__(v309, 27);
	v318 = v308 - 1894007588 + v289 + ((v301 | v303) & v297 | v301 & v303) + v319;
	v320 = __ROR4__(v217 ^ v201 ^ v258 ^ v294, 31);
	v321 = v320;
	v322 = v320 - 1894007588 + v303 + ((v318 | v316) & v311 | v318 & v316);
	v324 = __ROR4__(v318, 27);
	v323 = v315 - 1894007588 + v297 + ((v309 | v311) & v303 | v309 & v311) + v324;
	v326 = __ROR4__(v318, 2);
	v325 = v326;
	v328 = __ROR4__(v231 ^ v207 ^ v264 ^ v306, 31);
	v327 = v328;
	v330 = __ROR4__(v323, 27);
	v329 = v322 + v330;
	v332 = __ROR4__(v323, 2);
	v331 = v332;
	v333 = __ROR4__(v591 ^ v217 ^ v277 ^ v314, 31);
	v334 = v327 - 1894007588 + v311;
	v335 = v333;
	v336 = v333 - 1894007588 + v316 + ((v329 | v331) & v325 | v329 & v331);
	v338 = __ROR4__(v329, 27);
	v337 = v334 + ((v323 | v325) & v316 | v323 & v325) + v338;
	v340 = __ROR4__(v329, 2);
	v339 = v340;
	v342 = __ROR4__(v238 ^ v231 ^ v280 ^ v321, 31);
	v341 = v342;
	v344 = __ROR4__(v244 ^ v591 ^ v286 ^ v327, 31);
	v343 = v344;
	v346 = __ROR4__(v337, 27);
	v345 = v336 + v346;
	v348 = __ROR4__(v337, 2);
	v347 = v348;
	v591 = v343;
	v349 = v341;
	v350 = v341 - 1894007588 + v325;
	v351 = (v337 | v339) & v331 | v337 & v339;
	v352 = v343 - 1894007588 + v331;
	v353 = (v345 | v348) & v339 | v345 & v348;
	v355 = __ROR4__(v251 ^ v238 ^ v294 ^ v335, 31);
	v354 = v355;
	v357 = __ROR4__(v345, 27);
	v356 = v350 + v351 + v357;
	v358 = v354;
	v360 = __ROR4__(v345, 2);
	v359 = v360;
	v361 = v354 - 1894007588;
	v362 = v356 | v360;
	v364 = __ROR4__(v356, 27);
	v363 = v352 + v353 + v364;
	v366 = __ROR4__(v356, 2);
	v365 = v366;
	v367 = v362 & v347 | v356 & v359;
	v368 = __ROR4__(v258 ^ v244 ^ v306 ^ v349, 31);
	v369 = v368;
	v370 = v368 - 1894007588 + v347;
	v371 = __ROR4__(v264 ^ v251 ^ v314 ^ v591, 31);
	v372 = v371;
	v373 = (v363 | v365) & v359 | v363 & v365;
	v375 = __ROR4__(v363, 27);
	v374 = v361 + v339 + v367 + v375;
	v377 = __ROR4__(v363, 2);
	v376 = v377;
	v378 = v374 | v377;
	v380 = __ROR4__(v374, 27);
	v379 = v370 + v373 + v380;
	v382 = __ROR4__(v374, 2);
	v381 = v382;
	v383 = __ROR4__(v277 ^ v258 ^ v321 ^ v358, 31);
	v384 = v383;
	v385 = v372 - 1894007588 + v359 + (v378 & v365 | v374 & v376);
	v386 = v383 - 1894007588 + v365;
	v387 = (v379 | v381) & v376 | v379 & v381;
	v389 = __ROR4__(v379, 27);
	v388 = v385 + v389;
	v391 = __ROR4__(v280 ^ v264 ^ v327 ^ v369, 31);
	v390 = v391;
	v393 = __ROR4__(v379, 2);
	v392 = v393;
	v394 = v390;
	v395 = v388 | v393;
	v396 = v386 + v387;
	v398 = __ROR4__(v388, 2);
	v397 = v398;
	v400 = __ROR4__(v388, 27);
	v399 = v396 + v400;
	v401 = __ROR4__(v286 ^ v277 ^ v335 ^ v372, 31);
	v402 = v401;
	v403 = v390 - 1894007588 + v376 + (v395 & v381 | v388 & v392);
	v404 = v401 - 1894007588 + v381;
	v405 = __ROR4__(v294 ^ v280 ^ v349 ^ v384, 31);
	v406 = v405;
	v407 = v404 + ((v399 | v397) & v392 | v399 & v397);
	v408 = v405;
	v410 = __ROR4__(v399, 27);
	v409 = v403 + v410;
	v412 = __ROR4__(v399, 2);
	v411 = v412;
	v413 = __ROR4__(v306 ^ v286 ^ v591 ^ v390, 31);
	v414 = v413;
	v416 = __ROR4__(v409, 27);
	v415 = v407 + v416;
	v418 = __ROR4__(v409, 2);
	v417 = v418;
	v419 = __ROR4__(v314 ^ v294 ^ v358 ^ v402, 31);
	v420 = v419;
	v421 = v408 - 1894007588 + v392 + ((v409 | v411) & v397 | v409 & v411);
	v422 = v419;
	v424 = __ROR4__(v415, 2);
	v423 = v424;
	v426 = __ROR4__(v415, 27);
	v425 = v421 + v426;
	v427 = v422 - 899497514;
	v428 = v414 - 1894007588 + v397;
	v429 = v314;
	v430 = __ROR4__(v321 ^ v306 ^ v369 ^ v406, 31);
	v431 = v428 + ((v415 | v417) & v411 | v415 & v417);
	v432 = v430;
	v433 = v427 + v411 + (v423 ^ v417 ^ v425);
	v434 = v430;
	v436 = __ROR4__(v425, 2);
	v435 = v436;
	v438 = __ROR4__(v425, 27);
	v437 = v431 + v438;
	v439 = __ROR4__(v327 ^ v429 ^ v372 ^ v414, 31);
	v440 = v439;
	v441 = v434 - 899497514 + v417 + (v435 ^ v423 ^ v437);
	v442 = v439;
	v444 = __ROR4__(v437, 27);
	v443 = v433 + v444;
	v446 = __ROR4__(v437, 2);
	v445 = v446;
	v447 = __ROR4__(v335 ^ v321 ^ v384 ^ v420, 31);
	v448 = v447;
	v449 = v447;
	v451 = __ROR4__(v443, 2);
	v450 = v451;
	v453 = __ROR4__(v443, 27);
	v452 = v441 + v453;
	v454 = v591 ^ v335;
	v456 = __ROR4__(v349 ^ v327 ^ v394 ^ v432, 31);
	v455 = v456;
	v458 = __ROR4__(v452, 27);
	v457 = v442 - 899497514 + v423 + (v445 ^ v435 ^ v443) + v458;
	v459 = v455;
	v461 = __ROR4__(v452, 2);
	v460 = v461;
	v462 = v449 - 899497514 + v435 + (v450 ^ v445 ^ v452);
	v463 = v358 ^ v349;
	v464 = __ROR4__(v454 ^ v402 ^ v440, 31);
	v465 = v464;
	v466 = v463 ^ v406 ^ v448;
	v467 = v455 - 899497514 + v445 + (v460 ^ v450 ^ v457);
	v469 = __ROR4__(v457, 27);
	v468 = v462 + v469;
	v471 = __ROR4__(v457, 2);
	v470 = v471;
	v472 = __ROR4__(v466, 31);
	v473 = v369 ^ v591;
	v591 = v472;
	v475 = __ROR4__(v468, 2);
	v474 = v475;
	v477 = __ROR4__(v468, 27);
	v476 = v467 + v477;
	v478 = v465 - 899497514 + v450 + (v470 ^ v460 ^ v468);
	v479 = __ROR4__(v473 ^ v414 ^ v459, 31);
	v480 = v372 ^ v358 ^ v420;
	v481 = v479;
	v482 = v479;
	v483 = v591 - 899497514 + v460 + (v474 ^ v470 ^ v476);
	v485 = __ROR4__(v476, 2);
	v484 = v485;
	v487 = __ROR4__(v476, 27);
	v486 = v478 + v487;
	v488 = v384 ^ v369 ^ v432;
	v489 = __ROR4__(v480 ^ v465, 31);
	v490 = v489;
	v491 = v372;
	v493 = __ROR4__(v486, 2);
	v492 = v493;
	v495 = __ROR4__(v488 ^ v591, 31);
	v494 = v495;
	v497 = __ROR4__(v486, 27);
	v496 = v483 + v497;
	v498 = v494;
	v500 = __ROR4__(v496, 27);
	v499 = v482 - 899497514 + v470 + (v484 ^ v474 ^ v486) + v500;
	v502 = __ROR4__(v496, 2);
	v501 = v502;
	v504 = __ROR4__(v394 ^ v491 ^ v440 ^ v481, 31);
	v503 = v504;
	v505 = v402 ^ v384;
	v507 = __ROR4__(v499, 27);
	v506 = v490 - 899497514 + v474 + (v492 ^ v484 ^ v496) + v507;
	v508 = v503;
	v509 = v494 - 899497514 + v484;
	v511 = __ROR4__(v499, 2);
	v510 = v511;
	v512 = v406 ^ v394;
	v513 = __ROR4__(v505 ^ v448 ^ v490, 31);
	v514 = v513;
	v516 = __ROR4__(v506, 27);
	v515 = v509 + (v501 ^ v492 ^ v499) + v516;
	v517 = v503 - 899497514 + v492;
	v519 = __ROR4__(v506, 2);
	v518 = v519;
	v520 = v517 + (v510 ^ v501 ^ v506);
	v521 = v519 ^ v510;
	v523 = __ROR4__(v515, 2);
	v522 = v523;
	v525 = __ROR4__(v515, 27);
	v524 = v520 + v525;
	v527 = __ROR4__(v512 ^ v459 ^ v494, 31);
	v526 = v527;
	v528 = v527 - 899497514 + v510 + (v522 ^ v518 ^ v524);
	v530 = __ROR4__(v524, 2);
	v529 = v530;
	v532 = __ROR4__(v524, 27);
	v531 = v514 - 899497514 + v501 + (v521 ^ v515) + v532;
	v534 = __ROR4__(v414 ^ v402 ^ v465 ^ v508, 31);
	v533 = v534;
	v535 = v534 - 899497514;
	v537 = __ROR4__(v420 ^ v406 ^ v591 ^ v514, 31);
	v536 = v537;
	v539 = __ROR4__(v531, 27);
	v538 = v528 + v539;
	v540 = v535 + v518;
	v542 = __ROR4__(v531, 2);
	v541 = v542;
	v543 = __ROR4__(v432 ^ v414 ^ v481 ^ v526, 31);
	v544 = v420;
	v545 = v543;
	v547 = __ROR4__(v538, 2);
	v546 = v547;
	v549 = __ROR4__(v538, 27);
	v548 = v540 + (v529 ^ v522 ^ v531) + v549;
	v550 = v536 - 899497514 + v522 + (v541 ^ v529 ^ v538);
	v552 = __ROR4__(v440 ^ v544 ^ v490 ^ v533, 31);
	v551 = v552;
	v553 = v545 - 899497514 + v529 + (v546 ^ v541 ^ v548);
	v555 = __ROR4__(v548, 2);
	v554 = v555;
	v557 = __ROR4__(v548, 27);
	v556 = v550 + v557;
	v558 = v448 ^ v432 ^ v498 ^ v536;
	v560 = __ROR4__(v550 + v557, 27);
	v559 = v553 + v560;
	v562 = __ROR4__(v556, 2);
	v561 = v562;
	v563 = __ROR4__(v558, 31);
	v564 = v563 - 899497514;
	v566 = __ROR4__(v559, 27);
	v565 = v551 - 899497514 + v541 + (v554 ^ v546 ^ v556) + v566;
	v568 = __ROR4__(v559, 2);
	v567 = v568;
	v569 = __ROR4__(v459 ^ v440 ^ v508 ^ v545, 31);
	v570 = v564 + v546 + (v561 ^ v554 ^ v559);
	v571 = v569 - 899497514 + v554;
	v573 = __ROR4__(v565, 27);
	v572 = v570 + v573;
	v574 = v571 + (v567 ^ v561 ^ v565);
	v576 = __ROR4__(v565, 2);
	v575 = v576;
	v578 = __ROR4__(v572, 27);
	v577 = v574 + v578;
	v579 = v575 ^ v567 ^ v572;
	v581 = __ROR4__(v465 ^ v448 ^ v514 ^ v551, 31);
	v580 = v581;
	v583 = __ROR4__(v572, 2);
	v582 = v583;
	v585 = __ROR4__(v577, 27);
	v584 = v585;

	free(v592);

	v587 = *(unsigned int *)result - 899497514 + v580 + v561 + v579 + v584;
	v588 = *(unsigned int *)(result + 4) + v577;
	v589 = *(unsigned int *)(result + 8) + v582;
	v590 = *(unsigned int *)(result + 12) + v575;
	*(unsigned int *)(result + 16) += v567;
	*(unsigned int *)result = v587;
	*(unsigned int *)(result + 4) = v588;
	*(unsigned int *)(result + 8) = v589;
	*(unsigned int *)(result + 12) = v590;
	return result;
}







char * getLastKeyResult_4F1B0_opt(char * result, char *a2)
{
	char  *v2; // r2@1
	int v8; // r3@3
	int v9; // r2@3
	int v10; // r4@3
	int v11; // r12@3
	int v12; // off@3
	int v13; // r11@3
	int v14; // r1@3
	int v15; // off@3
	int v16; // off@3
	int v17; // r8@3
	int v18; // r7@3
	int v19; // off@3
	int v20; // r2@3
	int v21; // off@3
	int v22; // r4@3
	int v23; // r8@3
	int v24; // r4@3
	int v25; // r3@3
	int v26; // off@3
	int v27; // r4@3
	int v28; // off@3
	int v29; // r6@3
	int v30; // r12@3
	int v31; // off@3
	int v32; // r6@3
	int v33; // off@3
	int v34; // r10@3
	int v35; // r1@3
	int v36; // off@3
	int v37; // r10@3
	int v38; // off@3
	int v39; // r8@3
	int v40; // off@3
	int v41; // r2@3
	int v42; // off@3
	int v43; // r7@3
	int v44; // r10@3
	int v45; // r7@3
	int v46; // r3@3
	int v47; // off@3
	int v48; // r7@3
	int v49; // off@3
	int v50; // r6@3
	int v51; // r4@3
	int v52; // off@3
	int v53; // r12@3
	int v54; // off@3
	int v55; // r7@3
	int v56; // r6@3
	int v57; // r1@3
	int v58; // off@3
	int v59; // r6@3
	int v60; // off@3
	int v61; // r10@3
	int v62; // r2@3
	int v63; // off@3
	int v64; // r10@3
	int v65; // off@3
	int v66; // r8@3
	int v67; // r3@3
	int v68; // off@3
	int v69; // r8@3
	int v70; // off@3
	int v71; // r7@3
	int v72; // off@3
	int v73; // r12@3
	int v74; // off@3
	int v75; // r6@3
	int v76; // r4@3
	int v77; // r1@3
	int v78; // off@3
	int v79; // r4@3
	int v80; // off@3
	int v81; // r6@3
	int v82; // off@3
	int v83; // r2@3
	int v84; // off@3
	int v85; // ST04_4@3
	int v86; // r8@3
	int v87; // off@3
	int v88; // ST08_4@3
	int v89; // r3@3
	int v90; // off@3
	int v91; // r6@3
	int v92; // off@3
	int v93; // off@3
	int v94; // ST30_4@3
	int v95; // r9@3
	int v96; // off@3
	int v97; // r12@3
	int v98; // off@3
	int v99; // off@3
	int v100; // ST2C_4@3
	int v101; // r7@3
	int v102; // off@3
	int v103; // r4@3
	int v104; // r12@3
	int v105; // off@3
	int v106; // r1@3
	int v107; // off@3
	int v108; // r6@3
	int v109; // r12@3
	int v110; // off@3
	int v111; // off@3
	int v112; // r3@3
	int v113; // r9@3
	int v114; // off@3
	int v115; // ST38_4@3
	int v116; // r3@3
	int v117; // off@3
	int v118; // r10@3
	int v119; // off@3
	int v120; // off@3
	int v121; // ST20_4@3
	int v122; // r9@3
	int v123; // off@3
	int v124; // r5@3
	int v125; // off@3
	int v126; // r6@3
	int v127; // r7@3
	int v128; // off@3
	int v129; // r8@3
	int v130; // r1@3
	int v131; // off@3
	int v132; // r2@3
	int v133; // off@3
	int v134; // off@3
	int v135; // ST1C_4@3
	int v136; // ST18_4@3
	int v137; // r12@3
	int v138; // r4@3
	int v139; // off@3
	int v140; // r8@3
	int v141; // off@3
	int v142; // off@3
	int v143; // ST14_4@3
	int v144; // r2@3
	int v145; // off@3
	int v146; // r3@3
	int v147; // off@3
	int v148; // r12@3
	int v149; // r4@3
	int v150; // r12@3
	int v151; // off@3
	int v152; // r6@3
	int v153; // r1@3
	int v154; // off@3
	int v155; // off@3
	int v156; // ST34_4@3
	int v157; // r7@3
	int v158; // r4@3
	int v159; // r6@3
	int v160; // off@3
	int v161; // r4@3
	int v162; // off@3
	int v163; // off@3
	int v164; // ST28_4@3
	int v165; // r2@3
	int v166; // off@3
	int v167; // ST10_4@3
	int v168; // r11@3
	int v169; // r5@3
	int v170; // off@3
	int v171; // r3@3
	int v172; // r2@3
	int v173; // off@3
	int v174; // r12@3
	int v175; // r9@3
	int v176; // r4@3
	int v177; // off@3
	int v178; // ST04_4@3
	int v179; // off@3
	int v180; // ST0C_4@3
	int v181; // r1@3
	int v182; // off@3
	int v183; // r12@3
	int v184; // off@3
	int v185; // r4@3
	int v186; // off@3
	int v187; // r10@3
	int v188; // off@3
	int v189; // off@3
	int v190; // ST24_4@3
	int v191; // r3@3
	int v192; // off@3
	int v193; // r5@3
	int v194; // off@3
	int v195; // r6@3
	int v196; // r9@3
	int v197; // r2@3
	int v198; // off@3
	int v199; // r6@3
	int v200; // off@3
	int v201; // ST08_4@3
	int v202; // r8@3
	int v203; // r1@3
	int v204; // off@3
	int v205; // off@3
	int v206; // r7@3
	int v207; // ST30_4@3
	int v208; // r4@3
	int v209; // r8@3
	int v210; // off@3
	int v211; // r9@3
	int v212; // off@3
	int v213; // r11@3
	int v214; // ST2C_4@3
	int v215; // r6@3
	int v216; // r12@3
	int v217; // r3@3
	int v218; // off@3
	int v219; // r5@3
	int v220; // off@3
	int v221; // r2@3
	int v222; // off@3
	int v223; // r12@3
	int v224; // off@3
	int v225; // r11@3
	int v226; // r1@3
	int v227; // off@3
	int v228; // r6@3
	int v229; // off@3
	int v230; // off@3
	int v231; // ST2C_4@3
	int v232; // r4@3
	int v233; // off@3
	int v234; // r2@3
	int v235; // off@3
	int v236; // r7@3
	int v237; // off@3
	int v238; // ST38_4@3
	int v239; // r8@3
	int v240; // off@3
	int v241; // r10@3
	int v242; // off@3
	int v243; // off@3
	int v244; // ST20_4@3
	int v245; // r9@3
	int v246; // off@3
	int v247; // r11@3
	int v248; // off@3
	int v249; // r5@3
	int v250; // off@3
	int v251; // ST1C_4@3
	int v252; // r10@3
	int v253; // off@3
	int v254; // r4@3
	int v255; // off@3
	int v256; // r6@3
	int v257; // off@3
	int v258; // ST18_4@3
	int v259; // r1@3
	int v260; // off@3
	int v261; // r5@3
	int v262; // off@3
	int v263; // off@3
	int v264; // ST14_4@3
	int v265; // r8@3
	int v266; // off@3
	int v267; // r12@3
	int v268; // r11@3
	int v269; // off@3
	int v270; // r12@3
	int v271; // r5@3
	int v272; // r12@3
	int v273; // off@3
	int v274; // r7@3
	int v275; // off@3
	int v276; // off@3
	int v277; // ST34_4@3
	int v278; // r9@3
	int v279; // off@3
	int v280; // ST28_4@3
	int v281; // r2@3
	int v282; // off@3
	int v283; // r12@3
	int v284; // off@3
	int v285; // off@3
	int v286; // ST10_4@3
	int v287; // r9@3
	int v288; // off@3
	int v289; // r1@3
	int v290; // off@3
	int v291; // r4@3
	int v292; // r2@3
	int v293; // off@3
	int v294; // ST04_4@3
	int v295; // r4@3
	int v296; // off@3
	int v297; // r9@3
	int v298; // off@3
	int v299; // r2@3
	int v300; // r7@3
	int v301; // r2@3
	int v302; // off@3
	int v303; // r6@3
	int v304; // off@3
	int v305; // off@3
	int v306; // ST0C_4@3
	int v307; // r12@3
	int v308; // r4@3
	int v309; // r12@3
	int v310; // off@3
	int v311; // r7@3
	int v312; // off@3
	int v313; // off@3
	int v314; // ST24_4@3
	int v315; // r11@3
	int v316; // r8@3
	int v317; // off@3
	int v318; // r4@3
	int v319; // off@3
	int v320; // off@3
	int v321; // ST08_4@3
	int v322; // r1@3
	int v323; // r9@3
	int v324; // off@3
	int v325; // r4@3
	int v326; // off@3
	int v327; // r2@3
	int v328; // off@3
	int v329; // r1@3
	int v330; // off@3
	int v331; // r12@3
	int v332; // off@3
	int v333; // off@3
	int v334; // r6@3
	int v335; // ST30_4@3
	int v336; // r7@3
	int v337; // r10@3
	int v338; // off@3
	int v339; // r1@3
	int v340; // off@3
	int v341; // r5@3
	int v342; // off@3
	int v343; // r8@3
	int v344; // off@3
	int v345; // r7@3
	int v346; // off@3
	int v347; // r3@3
	int v348; // off@3
	int v349; // ST2C_4@3
	int v350; // r4@3
	int v351; // r5@3
	int v352; // r12@3
	int v353; // r8@3
	int v354; // r11@3
	int v355; // off@3
	int v356; // r5@3
	int v357; // off@3
	int v358; // ST38_4@3
	int v359; // r7@3
	int v360; // off@3
	int v361; // r6@3
	int v362; // r9@3
	int v363; // r8@3
	int v364; // off@3
	int v365; // r4@3
	int v366; // off@3
	int v367; // r11@3
	int v368; // off@3
	int v369; // ST20_4@3
	int v370; // r3@3
	int v371; // off@3
	int v372; // ST1C_4@3
	int v373; // r5@3
	int v374; // r11@3
	int v375; // off@3
	int v376; // r8@3
	int v377; // off@3
	int v378; // r1@3
	int v379; // r5@3
	int v380; // off@3
	int v381; // r3@3
	int v382; // off@3
	int v383; // off@3
	int v384; // ST18_4@3
	int v385; // r12@3
	int v386; // r4@3
	int v387; // r1@3
	int v388; // r12@3
	int v389; // off@3
	int v390; // r7@3
	int v391; // off@3
	int v392; // r5@3
	int v393; // off@3
	int v394; // ST14_4@3
	int v395; // r11@3
	int v396; // r1@3
	int v397; // r4@3
	int v398; // off@3
	int v399; // r1@3
	int v400; // off@3
	int v401; // off@3
	int v402; // ST34_4@3
	int v403; // r10@3
	int v404; // r3@3
	int v405; // off@3
	int v406; // ST28_4@3
	int v407; // r12@3
	int v408; // r6@3
	int v409; // r10@3
	int v410; // off@3
	int v411; // r1@3
	int v412; // off@3
	int v413; // off@3
	int v414; // ST10_4@3
	int v415; // r12@3
	int v416; // off@3
	int v417; // r3@3
	int v418; // off@3
	int v419; // off@3
	int v420; // ST04_4@3
	int v421; // r9@3
	int v422; // r10@3
	int v423; // r8@3
	int v424; // off@3
	int v425; // r9@3
	int v426; // off@3
	int v427; // r5@3
	int v428; // r10@3
	int v429; // r4@3
	int v430; // off@3
	int v431; // ST24_4@3
	int v432; // ST0C_4@3
	int v433; // r6@3
	int v434; // r5@3
	int v435; // r10@3
	int v436; // off@3
	int v437; // r9@3
	int v438; // off@3
	int v439; // off@3
	int v440; // ST24_4@3
	int v441; // r7@3
	int v442; // r3@3
	int v443; // r6@3
	int v444; // off@3
	int v445; // r1@3
	int v446; // off@3
	int v447; // off@3
	int v448; // ST08_4@3
	int v449; // r5@3
	int v450; // r11@3
	int v451; // off@3
	int v452; // r7@3
	int v453; // off@3
	int v454; // r4@3
	int v455; // r2@3
	int v456; // off@3
	int v457; // r8@3
	int v458; // off@3
	int v459; // ST30_4@3
	int v460; // r12@3
	int v461; // off@3
	int v462; // r6@3
	int v463; // r5@3
	int v464; // off@3
	int v465; // ST2C_4@3
	int v466; // r10@3
	int v467; // r2@3
	int v468; // r6@3
	int v469; // off@3
	int v470; // r5@3
	int v471; // off@3
	int v472; // off@3
	int v473; // r8@3
	int v474; // r9@3
	int v475; // off@3
	int v476; // r2@3
	int v477; // off@3
	int v478; // r1@3
	int v479; // off@3
	int v480; // r11@3
	int v481; // ST38_4@3
	int v482; // r10@3
	int v483; // r7@3
	int v484; // r3@3
	int v485; // off@3
	int v486; // r1@3
	int v487; // off@3
	int v488; // r8@3
	int v489; // off@3
	int v490; // ST20_4@3
	int v491; // r2@3
	int v492; // r4@3
	int v493; // off@3
	int v494; // r11@3
	int v495; // off@3
	int v496; // r7@3
	int v497; // off@3
	int v498; // ST1C_4@3
	int v499; // r10@3
	int v500; // off@3
	int v501; // r8@3
	int v502; // off@3
	int v503; // r1@3
	int v504; // off@3
	int v505; // r6@3
	int v506; // r2@3
	int v507; // off@3
	int v508; // ST18_4@3
	int v509; // r5@3
	int v510; // r3@3
	int v511; // off@3
	int v512; // r7@3
	int v513; // off@3
	int v514; // ST14_4@3
	int v515; // r5@3
	int v516; // off@3
	int v517; // r12@3
	int v518; // r4@3
	int v519; // off@3
	int v520; // r12@3
	int v521; // r1@3
	int v522; // r2@3
	int v523; // off@3
	int v524; // r12@3
	int v525; // off@3
	int v526; // r7@3
	int v527; // off@3
	int v528; // r9@3
	int v529; // r3@3
	int v530; // off@3
	int v531; // r12@3
	int v532; // off@3
	int v533; // r6@3
	int v534; // off@3
	int v535; // r5@3
	int v536; // r10@3
	int v537; // off@3
	int v538; // r9@3
	int v539; // off@3
	int v540; // r4@3
	int v541; // r5@3
	int v542; // off@3
	int v543; // off@3
	int v544; // r11@3
	int v545; // ST04_4@3
	int v546; // r7@3
	int v547; // off@3
	int v548; // r4@3
	int v549; // off@3
	int v550; // r2@3
	int v551; // r6@3
	int v552; // off@3
	int v553; // r3@3
	int v554; // r9@3
	int v555; // off@3
	int v556; // r4@3
	int v557; // off@3
	int v558; // r11@3
	int v559; // r3@3
	int v560; // off@3
	int v561; // r10@3
	int v562; // off@3
	int v563; // off@3
	int v564; // r12@3
	int v565; // r4@3
	int v566; // off@3
	int v567; // r11@3
	int v568; // off@3
	int v569; // off@3
	int v570; // r3@3
	int v571; // r9@3
	int v572; // r3@3
	int v573; // off@3
	int v574; // r1@3
	int v575; // r4@3
	int v576; // off@3
	int v577; // r1@3
	int v578; // off@3
	int v579; // r5@3
	int v580; // r6@3
	int v581; // off@3
	int v582; // r3@3
	int v583; // off@3
	int v584; // r7@3
	int v585; // off@3
	int *v586; // r2@3
	int v587; // r10@5
	int v588; // r1@5
	int v589; // r3@5
	int v590; // r4@5 
	int v591; // [sp+3Ch] [bp-6Ch]@3
	char * v592; // [sp+40h] [bp-68h]@2
	int v593; // [sp+44h] [bp-64h]@3
	int v594; // [sp+48h] [bp-60h]@3
	int v595; // [sp+4Ch] [bp-5Ch]@3
	int v596; // [sp+50h] [bp-58h]@3
	int v597; // [sp+54h] [bp-54h]@3
	int v598; // [sp+58h] [bp-50h]@3
	int v599; // [sp+5Ch] [bp-4Ch]@3
	int v600; // [sp+60h] [bp-48h]@3
	int v601; // [sp+64h] [bp-44h]@3
	int v602; // [sp+68h] [bp-40h]@3
	int v603; // [sp+6Ch] [bp-3Ch]@3
	int v604; // [sp+70h] [bp-38h]@3
	int v605; // [sp+74h] [bp-34h]@3
	int v606; // [sp+78h] [bp-30h]@3
	int v607; // [sp+7Ch] [bp-2Ch]@3

	v592 = (char *)malloc(64);
	memset(v592, 0, 64);
	//四个字节每次，高位放低位
	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 4; j++){
			v592[4 * i + j] = a2[4 * i + (3 - j)];
		}
	}


	v593 = *(unsigned int *)(v592 + 4);
	v594 = *(unsigned int *)(v592 + 8);
	v595 = *(unsigned int *)(v592 + 12);
	v596 = *(unsigned int *)(v592 + 16);

	v597 = *(unsigned int *)(v592 + 20);
	v598 = *(unsigned int *)(v592 + 24);
	v599 = *(unsigned int *)(v592 + 28);
	v600 = *(unsigned int *)(v592 + 32);
	v601 = *(unsigned int *)(v592 + 36);
	v602 = *(unsigned int *)(v592 + 40);
	v603 = *(unsigned int *)(v592 + 44);
	v604 = *(unsigned int *)(v592 + 48);
	v605 = *(unsigned int *)(v592 + 52);
	v606 = *(unsigned int *)(v592 + 56);
	v607 = *(unsigned int *)(v592 + 60);

	v8 = *(unsigned int *)(result + 8);
	v9 = *(unsigned int *)(result + 12);
	v10 = *(unsigned int *)(result + 4);
	v12 = __ROR4__(v10, 2);
	v11 = v12;
	v13 = v12 ^ v8;
	int temp_result = *(unsigned int *)(result);
	v15 = __ROR4__(temp_result, 2);
	v14 = v15;
	v16 = __ROR4__(temp_result, 27);
	int kkk = *(unsigned int *)v592 + 1518500249 + *(unsigned int *)(result + 16) + v16;
	v17 = *(unsigned int *)v592 + 1518500249 + *(unsigned int *)(result + 16) + v16 + ((v9 ^ v8) & v10 ^ v9);
	v19 = __ROR4__(v17, 27);
	v18 = v593 + 1518500249 + v9 + (v13 & *(unsigned int *)result ^ v8) + v19;
	v21 = __ROR4__(v17, 2);
	v20 = v21;
	v22 = v17 & (v11 ^ v14) ^ v11;
	v23 = v21 ^ v14;
	v24 = v594 + 1518500249 + v8 + v22;
	v26 = __ROR4__(v18, 2);
	v25 = v26;
	v28 = __ROR4__(v18, 27);
	v27 = v24 + v28;
	v29 = v595 + 1518500249 + v11 + (v23 & v18 ^ v14);
	v31 = __ROR4__(v27, 2);
	v30 = v31;
	v33 = __ROR4__(v27, 27);
	v32 = v29 + v33;
	v34 = v596 + 1518500249 + v14 + ((v25 ^ v20) & v27 ^ v20);
	v36 = __ROR4__(v32, 2);
	v35 = v36;
	v38 = __ROR4__(v32, 27);
	v37 = v34 + v38;
	v40 = __ROR4__(v37, 27);
	v39 = v597 + 1518500249 + v20 + ((v30 ^ v25) & v32 ^ v25) + v40;
	v42 = __ROR4__(v37, 2);
	v41 = v42;
	v43 = (v35 ^ v30) & v37 ^ v30;
	v44 = v42 ^ v35;
	v45 = v598 + 1518500249 + v25 + v43;
	v47 = __ROR4__(v39, 2);
	v46 = v47;
	v49 = __ROR4__(v39, 27);
	v48 = v45 + v49;
	v50 = (v46 ^ v41) & v48 ^ v41;
	v52 = __ROR4__(v48, 27);
	v51 = v599 + 1518500249 + v30 + (v44 & v39 ^ v35) + v52;
	v54 = __ROR4__(v48, 2);
	v53 = v54;
	v55 = v54 ^ v46;
	v56 = v600 + 1518500249 + v35 + v50;
	v58 = __ROR4__(v51, 2);
	v57 = v58;
	v60 = __ROR4__(v51, 27);
	v59 = v56 + v60;
	v61 = v601 + 1518500249 + v41 + (v55 & v51 ^ v46);
	v63 = __ROR4__(v59, 2);
	v62 = v63;
	v65 = __ROR4__(v59, 27);
	v64 = v61 + v65;
	v66 = v602 + 1518500249 + v46 + ((v57 ^ v53) & v59 ^ v53);
	v68 = __ROR4__(v64, 2);
	v67 = v68;
	v70 = __ROR4__(v64, 27);
	v69 = v66 + v70;
	v72 = __ROR4__(v69, 27);
	v71 = v603 + 1518500249 + v53 + ((v62 ^ v57) & v64 ^ v57) + v72;
	v74 = __ROR4__(v69, 2);
	v73 = v74;
	v75 = v74 ^ v67;
	v76 = v604 + 1518500249 + v57 + ((v67 ^ v62) & v69 ^ v62);
	v78 = __ROR4__(v71, 2);
	v77 = v78;
	v80 = __ROR4__(v71, 27);
	v79 = v76 + v80;
	v82 = __ROR4__(v79, 27);
	v81 = v605 + 1518500249 + v62 + (v75 & v71 ^ v67) + v82;
	v84 = __ROR4__(v79, 2);
	v83 = v84;
	v85 = v606 + 1518500249 + v67 + ((v77 ^ v73) & v79 ^ v73);
	v86 = (v84 ^ v77) & v81;
	v87 = __ROR4__(v594 ^ *(unsigned int *)v592 ^ v600 ^ v605, 31);
	v88 = v87;
	v90 = __ROR4__(v81, 2);
	v89 = v90;
	v92 = __ROR4__(v81, 27);
	v91 = v85 + v92;
	v93 = __ROR4__(v595 ^ v593 ^ v601 ^ v606, 31);

	v94 = v93;
	v96 = __ROR4__(v91, 2);
	v95 = v96;
	v98 = __ROR4__(v91, 27);
	v97 = v607 + 1518500249 + v73 + (v86 ^ v77) + v98;
	v99 = __ROR4__(v596 ^ v594 ^ v602 ^ v607, 31);
	v100 = v99;
	v102 = __ROR4__(v97, 2);
	v101 = v102;
	v103 = (v95 ^ v89) & v97 ^ v89;
	v105 = __ROR4__(v97, 27);
	v104 = v88 + 1518500249 + v77 + ((v89 ^ v83) & v91 ^ v83) + v105;
	v107 = __ROR4__(v104, 2);
	v106 = v107;
	v108 = (v101 ^ v95) & v104;
	v110 = __ROR4__(v104, 27);
	v109 = v94 + 1518500249 + v83 + v103 + v110;
	v111 = __ROR4__(v597 ^ v595 ^ v603 ^ v88, 31);
	v591 = v111;
	v112 = v100 + 1518500249 + v89 + (v108 ^ v95);
	v113 = v111 + 1518500249 + v95;
	v114 = __ROR4__(v598 ^ v596 ^ v604 ^ v94, 31);
	v115 = v114;
	v117 = __ROR4__(v109, 27);
	v116 = v112 + v117;
	v119 = __ROR4__(v109, 2);
	v118 = v119;
	v120 = __ROR4__(v599 ^ v597 ^ v605 ^ v100, 31);
	v121 = v120;
	v123 = __ROR4__(v116, 27);
	v122 = v113 + ((v106 ^ v101) & v109 ^ v101) + v123;
	v125 = __ROR4__(v116, 2);
	v124 = v125;
	v126 = v125 ^ v118;
	v128 = __ROR4__(v122, 27);
	v127 = v115 + 1859775393 + v101 + (v118 ^ v106 ^ v116) + v128;
	v129 = v121 + 1859775393 + v106;
	v131 = __ROR4__(v122, 2);
	v130 = v131;
	v133 = __ROR4__(v600 ^ v598 ^ v606 ^ v591, 31);
	v132 = v133;
	v134 = __ROR4__(v601 ^ v599 ^ v607 ^ v115, 31);
	v135 = v132;
	v136 = v134;
	v137 = v134;
	v139 = __ROR4__(v127, 27);
	v138 = v129 + (v126 ^ v122) + v139;
	v141 = __ROR4__(v127, 2);
	v140 = v141;
	v142 = __ROR4__(v602 ^ v600 ^ v88 ^ v121, 31);
	v143 = v142;
	v145 = __ROR4__(v138, 27);
	v144 = v132 + 1859775393 + v118 + (v130 ^ v124 ^ v127) + v145;
	v147 = __ROR4__(v138, 2);
	v146 = v147;
	v148 = v137 + 1859775393 + v124 + (v140 ^ v130 ^ v138);
	v149 = v147 ^ v140;
	v151 = __ROR4__(v144, 27);
	v150 = v148 + v151;
	v152 = v143 + 1859775393 + v130;
	v154 = __ROR4__(v144, 2);
	v153 = v154;
	v155 = __ROR4__(v603 ^ v601 ^ v94 ^ v135, 31);
	v156 = v155;
	v157 = v155 + 1859775393;
	v158 = v152 + (v149 ^ v144);
	v160 = __ROR4__(v150, 2);
	v159 = v160;
	v162 = __ROR4__(v150, 27);
	v161 = v158 + v162;
	v163 = __ROR4__(v604 ^ v602 ^ v100 ^ v136, 31);
	v164 = v163;
	v165 = v163 + 1859775393;
	v166 = __ROR4__(v605 ^ v603 ^ v591 ^ v143, 31);
	v167 = v166;
	v168 = v166;
	v170 = __ROR4__(v161, 27);
	v169 = v157 + v140 + (v153 ^ v146 ^ v150) + v170;
	v171 = v165 + v146;
	v173 = __ROR4__(v161, 2);
	v172 = v173;
	v174 = v171 + (v159 ^ v153 ^ v161);
	v175 = v168 + 1859775393 + v153;
	v176 = v173 ^ v159;
	v177 = __ROR4__(v606 ^ v604 ^ v115 ^ v156, 31);
	v178 = v177;
	v179 = __ROR4__(v607 ^ v605 ^ v121 ^ v164, 31);
	v180 = v179;
	v182 = __ROR4__(v169, 2);
	v181 = v182;
	v184 = __ROR4__(v169, 27);
	v183 = v174 + v184;
	v186 = __ROR4__(v183, 27);
	v185 = v175 + (v176 ^ v169) + v186;
	v188 = __ROR4__(v183, 2);
	v187 = v188;
	v189 = __ROR4__(v88 ^ v606 ^ v135 ^ v167, 31);
	v190 = v189;
	v192 = __ROR4__(v185, 27);
	v191 = v178 + 1859775393 + v159 + (v181 ^ v172 ^ v183) + v192;
	v194 = __ROR4__(v185, 2);
	v193 = v194;
	v195 = v180 + 1859775393 + v172 + (v187 ^ v181 ^ v185);
	v196 = v100 ^ v88 ^ v143;
	v198 = __ROR4__(v94 ^ v607 ^ v136 ^ v178, 31);
	v197 = v198;
	v200 = __ROR4__(v191, 27);
	v199 = v195 + v200;
	v201 = v197;
	v202 = v190 + 1859775393 + v181;
	v204 = __ROR4__(v191, 2);
	v203 = v204;
	v205 = __ROR4__(v196 ^ v180, 31);
	v206 = v591 ^ v94;
	v207 = v205;
	v208 = v205;
	v210 = __ROR4__(v199, 27);
	v209 = v202 + (v193 ^ v187 ^ v191) + v210;
	v212 = __ROR4__(v199, 2);
	v211 = v212;
	v213 = v100;
	v214 = v197 + 1859775393 + v187 + (v203 ^ v193 ^ v199);
	v215 = v115 ^ v213 ^ v164;
	v216 = v208 + 1859775393 + v193 + (v212 ^ v203 ^ v209);
	v218 = __ROR4__(v206 ^ v156 ^ v190, 31);
	v217 = v218;
	v220 = __ROR4__(v209, 2);
	v219 = v220;
	v222 = __ROR4__(v209, 27);
	v221 = v214 + v222;
	v224 = __ROR4__(v214 + v222, 27);
	v223 = v216 + v224;
	v225 = v217 + 1859775393 + v203;
	v227 = __ROR4__(v221, 2);
	v226 = v227;
	v229 = __ROR4__(v215 ^ v201, 31);
	v228 = v229;
	v230 = __ROR4__(v121 ^ v591 ^ v167 ^ v207, 31);
	v231 = v228;
	v591 = v230;
	v233 = __ROR4__(v223, 27);
	v232 = v225 + (v219 ^ v211 ^ v221) + v233;
	v235 = __ROR4__(v223, 2);
	v234 = v235;
	v236 = v235 ^ v226 ^ v232;
	v237 = __ROR4__(v135 ^ v115 ^ v178 ^ v217, 31);
	v238 = v237;
	v240 = __ROR4__(v232, 2);
	v239 = v240;
	v242 = __ROR4__(v232, 27);
	v241 = v228 + 1859775393 + v211 + (v226 ^ v219 ^ v223) + v242;
	v243 = __ROR4__(v136 ^ v121 ^ v180 ^ v228, 31);
	v244 = v243;
	v246 = __ROR4__(v143 ^ v135 ^ v190 ^ v591, 31);
	v245 = v246;
	v248 = __ROR4__(v241, 2);
	v247 = v248;
	v250 = __ROR4__(v241, 27);
	v249 = v591 + 1859775393 + v219 + v236 + v250;
	v251 = v245;
	v253 = __ROR4__(v249, 27);
	v252 = v238 + 1859775393 + v226 + (v239 ^ v234 ^ v241) + v253;
	v255 = __ROR4__(v249, 2);
	v254 = v255;
	v256 = v255 ^ v247;
	v257 = __ROR4__(v156 ^ v136 ^ v201 ^ v238, 31);
	v258 = v257;
	v260 = __ROR4__(v252, 2);
	v259 = v260;
	v262 = __ROR4__(v252, 27);
	v261 = v244 + 1859775393 + v234 + (v247 ^ v239 ^ v249) + v262;
	v263 = __ROR4__(v164 ^ v143 ^ v207 ^ v244, 31);
	v264 = v263;
	v266 = __ROR4__(v261, 27);
	v265 = v245 + 1859775393 + v239 + (v256 ^ v252) + v266;
	v267 = v258 + 1859775393 + v247;
	v269 = __ROR4__(v261, 2);
	v268 = v269;
	v270 = v267 + (v259 ^ v254 ^ v261);
	v271 = v265 | v269;
	v273 = __ROR4__(v265, 27);
	v272 = v270 + v273;
	v275 = __ROR4__(v265, 2);
	v274 = v275;
	v276 = __ROR4__(v167 ^ v156 ^ v217 ^ v245, 31);
	v277 = v276;
	v278 = v276 - 1894007588 + v259 + ((v272 | v274) & v268 | v272 & v274);
	v279 = __ROR4__(v178 ^ v164 ^ v231 ^ v258, 31);
	v280 = v279;
	v282 = __ROR4__(v272, 27);
	v281 = v264 - 1894007588 + v254 + (v271 & v259 | v265 & v268) + v282;
	v284 = __ROR4__(v272, 2);
	v283 = v284;
	v285 = __ROR4__(v180 ^ v167 ^ v591 ^ v264, 31);
	v286 = v285;
	v288 = __ROR4__(v281, 27);
	v287 = v278 + v288;
	v290 = __ROR4__(v281, 2);
	v289 = v290;
	v291 = (v281 | v283) & v274 | v281 & v283;
	v292 = (v287 | v290) & v283 | v287 & v290;
	v293 = __ROR4__(v190 ^ v178 ^ v238 ^ v277, 31);
	v294 = v293;
	v296 = __ROR4__(v287, 27);
	v295 = v280 - 1894007588 + v268 + v291 + v296;
	v298 = __ROR4__(v287, 2);
	v297 = v298;
	v299 = v286 - 1894007588 + v274 + v292;
	v300 = v295 | v298;
	v302 = __ROR4__(v295, 27);
	v301 = v299 + v302;
	v304 = __ROR4__(v295, 2);
	v303 = v304;
	v305 = __ROR4__(v201 ^ v180 ^ v244 ^ v280, 31);
	v306 = v305;
	v307 = v294 - 1894007588 + v283 + (v300 & v289 | v295 & v297);
	v308 = v305;
	v310 = __ROR4__(v301, 27);
	v309 = v307 + v310;
	v312 = __ROR4__(v301, 2);
	v311 = v312;
	v313 = __ROR4__(v207 ^ v190 ^ v251 ^ v286, 31);
	v314 = v313;
	v315 = v313;
	v317 = __ROR4__(v309, 2);
	v316 = v317;
	v319 = __ROR4__(v309, 27);
	v318 = v308 - 1894007588 + v289 + ((v301 | v303) & v297 | v301 & v303) + v319;
	v320 = __ROR4__(v217 ^ v201 ^ v258 ^ v294, 31);
	v321 = v320;
	v322 = v320 - 1894007588 + v303 + ((v318 | v316) & v311 | v318 & v316);
	v324 = __ROR4__(v318, 27);
	v323 = v315 - 1894007588 + v297 + ((v309 | v311) & v303 | v309 & v311) + v324;
	v326 = __ROR4__(v318, 2);
	v325 = v326;
	v328 = __ROR4__(v231 ^ v207 ^ v264 ^ v306, 31);
	v327 = v328;
	v330 = __ROR4__(v323, 27);
	v329 = v322 + v330;
	v332 = __ROR4__(v323, 2);
	v331 = v332;
	v333 = __ROR4__(v591 ^ v217 ^ v277 ^ v314, 31);
	v334 = v327 - 1894007588 + v311;
	v335 = v333;
	v336 = v333 - 1894007588 + v316 + ((v329 | v331) & v325 | v329 & v331);
	v338 = __ROR4__(v329, 27);
	v337 = v334 + ((v323 | v325) & v316 | v323 & v325) + v338;
	v340 = __ROR4__(v329, 2);
	v339 = v340;
	v342 = __ROR4__(v238 ^ v231 ^ v280 ^ v321, 31);
	v341 = v342;
	v344 = __ROR4__(v244 ^ v591 ^ v286 ^ v327, 31);
	v343 = v344;
	v346 = __ROR4__(v337, 27);
	v345 = v336 + v346;
	v348 = __ROR4__(v337, 2);
	v347 = v348;
	v591 = v343;
	v349 = v341;
	v350 = v341 - 1894007588 + v325;
	v351 = (v337 | v339) & v331 | v337 & v339;
	v352 = v343 - 1894007588 + v331;
	v353 = (v345 | v348) & v339 | v345 & v348;
	v355 = __ROR4__(v251 ^ v238 ^ v294 ^ v335, 31);
	v354 = v355;
	v357 = __ROR4__(v345, 27);
	v356 = v350 + v351 + v357;
	v358 = v354;
	v360 = __ROR4__(v345, 2);
	v359 = v360;
	v361 = v354 - 1894007588;
	v362 = v356 | v360;
	v364 = __ROR4__(v356, 27);
	v363 = v352 + v353 + v364;
	v366 = __ROR4__(v356, 2);
	v365 = v366;
	v367 = v362 & v347 | v356 & v359;
	v368 = __ROR4__(v258 ^ v244 ^ v306 ^ v349, 31);
	v369 = v368;
	v370 = v368 - 1894007588 + v347;
	v371 = __ROR4__(v264 ^ v251 ^ v314 ^ v591, 31);
	v372 = v371;
	v373 = (v363 | v365) & v359 | v363 & v365;
	v375 = __ROR4__(v363, 27);
	v374 = v361 + v339 + v367 + v375;
	v377 = __ROR4__(v363, 2);
	v376 = v377;
	v378 = v374 | v377;
	v380 = __ROR4__(v374, 27);
	v379 = v370 + v373 + v380;
	v382 = __ROR4__(v374, 2);
	v381 = v382;
	v383 = __ROR4__(v277 ^ v258 ^ v321 ^ v358, 31);
	v384 = v383;
	v385 = v372 - 1894007588 + v359 + (v378 & v365 | v374 & v376);
	v386 = v383 - 1894007588 + v365;
	v387 = (v379 | v381) & v376 | v379 & v381;
	v389 = __ROR4__(v379, 27);
	v388 = v385 + v389;
	v391 = __ROR4__(v280 ^ v264 ^ v327 ^ v369, 31);
	v390 = v391;
	v393 = __ROR4__(v379, 2);
	v392 = v393;
	v394 = v390;
	v395 = v388 | v393;
	v396 = v386 + v387;
	v398 = __ROR4__(v388, 2);
	v397 = v398;
	v400 = __ROR4__(v388, 27);
	v399 = v396 + v400;
	v401 = __ROR4__(v286 ^ v277 ^ v335 ^ v372, 31);
	v402 = v401;
	v403 = v390 - 1894007588 + v376 + (v395 & v381 | v388 & v392);
	v404 = v401 - 1894007588 + v381;
	v405 = __ROR4__(v294 ^ v280 ^ v349 ^ v384, 31);
	v406 = v405;
	v407 = v404 + ((v399 | v397) & v392 | v399 & v397);
	v408 = v405;
	v410 = __ROR4__(v399, 27);
	v409 = v403 + v410;
	v412 = __ROR4__(v399, 2);
	v411 = v412;
	v413 = __ROR4__(v306 ^ v286 ^ v591 ^ v390, 31);
	v414 = v413;
	v416 = __ROR4__(v409, 27);
	v415 = v407 + v416;
	v418 = __ROR4__(v409, 2);
	v417 = v418;
	v419 = __ROR4__(v314 ^ v294 ^ v358 ^ v402, 31);
	v420 = v419;
	v421 = v408 - 1894007588 + v392 + ((v409 | v411) & v397 | v409 & v411);
	v422 = v419;
	v424 = __ROR4__(v415, 2);
	v423 = v424;
	v426 = __ROR4__(v415, 27);
	v425 = v421 + v426;
	v427 = v422 - 899497514;
	v428 = v414 - 1894007588 + v397;
	v429 = v314;
	v430 = __ROR4__(v321 ^ v306 ^ v369 ^ v406, 31);
	v431 = v428 + ((v415 | v417) & v411 | v415 & v417);
	v432 = v430;
	v433 = v427 + v411 + (v423 ^ v417 ^ v425);
	v434 = v430;
	v436 = __ROR4__(v425, 2);
	v435 = v436;
	v438 = __ROR4__(v425, 27);
	v437 = v431 + v438;
	v439 = __ROR4__(v327 ^ v429 ^ v372 ^ v414, 31);
	v440 = v439;
	v441 = v434 - 899497514 + v417 + (v435 ^ v423 ^ v437);
	v442 = v439;
	v444 = __ROR4__(v437, 27);
	v443 = v433 + v444;
	v446 = __ROR4__(v437, 2);
	v445 = v446;
	v447 = __ROR4__(v335 ^ v321 ^ v384 ^ v420, 31);
	v448 = v447;
	v449 = v447;
	v451 = __ROR4__(v443, 2);
	v450 = v451;
	v453 = __ROR4__(v443, 27);
	v452 = v441 + v453;
	v454 = v591 ^ v335;
	v456 = __ROR4__(v349 ^ v327 ^ v394 ^ v432, 31);
	v455 = v456;
	v458 = __ROR4__(v452, 27);
	v457 = v442 - 899497514 + v423 + (v445 ^ v435 ^ v443) + v458;
	v459 = v455;
	v461 = __ROR4__(v452, 2);
	v460 = v461;
	v462 = v449 - 899497514 + v435 + (v450 ^ v445 ^ v452);
	v463 = v358 ^ v349;
	v464 = __ROR4__(v454 ^ v402 ^ v440, 31);
	v465 = v464;
	v466 = v463 ^ v406 ^ v448;
	v467 = v455 - 899497514 + v445 + (v460 ^ v450 ^ v457);
	v469 = __ROR4__(v457, 27);
	v468 = v462 + v469;
	v471 = __ROR4__(v457, 2);
	v470 = v471;
	v472 = __ROR4__(v466, 31);
	v473 = v369 ^ v591;
	v591 = v472;
	v475 = __ROR4__(v468, 2);
	v474 = v475;
	v477 = __ROR4__(v468, 27);
	v476 = v467 + v477;
	v478 = v465 - 899497514 + v450 + (v470 ^ v460 ^ v468);
	v479 = __ROR4__(v473 ^ v414 ^ v459, 31);
	v480 = v372 ^ v358 ^ v420;
	v481 = v479;
	v482 = v479;
	v483 = v591 - 899497514 + v460 + (v474 ^ v470 ^ v476);
	v485 = __ROR4__(v476, 2);
	v484 = v485;
	v487 = __ROR4__(v476, 27);
	v486 = v478 + v487;
	v488 = v384 ^ v369 ^ v432;
	v489 = __ROR4__(v480 ^ v465, 31);
	v490 = v489;
	v491 = v372;
	v493 = __ROR4__(v486, 2);
	v492 = v493;
	v495 = __ROR4__(v488 ^ v591, 31);
	v494 = v495;
	v497 = __ROR4__(v486, 27);
	v496 = v483 + v497;
	v498 = v494;
	v500 = __ROR4__(v496, 27);
	v499 = v482 - 899497514 + v470 + (v484 ^ v474 ^ v486) + v500;
	v502 = __ROR4__(v496, 2);
	v501 = v502;
	v504 = __ROR4__(v394 ^ v491 ^ v440 ^ v481, 31);
	v503 = v504;
	v505 = v402 ^ v384;
	v507 = __ROR4__(v499, 27);
	v506 = v490 - 899497514 + v474 + (v492 ^ v484 ^ v496) + v507;
	v508 = v503;
	v509 = v494 - 899497514 + v484;
	v511 = __ROR4__(v499, 2);
	v510 = v511;
	v512 = v406 ^ v394;
	v513 = __ROR4__(v505 ^ v448 ^ v490, 31);
	v514 = v513;
	v516 = __ROR4__(v506, 27);
	v515 = v509 + (v501 ^ v492 ^ v499) + v516;

	v521 = __ROR4__(v506, 2) ^ v510;

	v522 = __ROR4__(v515, 2);

	v524 = v503 - 899497514 + v492 + (v510 ^ v501 ^ v506) + __ROR4__(v515, 27);
	v529 = __ROR4__(v524, 2);
	v531 = v514 - 899497514 + v501 + (v521 ^ v515) + __ROR4__(v524, 27);
	v533 = __ROR4__(v414 ^ v402 ^ v465 ^ v508, 31);
	v536 = __ROR4__(v420 ^ v406 ^ v591 ^ v514, 31);
	v538 = __ROR4__(v512 ^ v459 ^ v494, 31) - 899497514 + v510 + (v522 ^ __ROR4__(v506, 2) ^ v524) + __ROR4__(v531, 27);
	v541 = __ROR4__(v531, 2);
	v544 = v420;
	v545 = __ROR4__(v432 ^ v414 ^ v481 ^ __ROR4__(v512 ^ v459 ^ v494, 31), 31);
	v546 = __ROR4__(v538, 2);
	v548 = __ROR4__(v414 ^ v402 ^ v465 ^ v508, 31) - 899497514 + __ROR4__(v506, 2) + (v529 ^ v522 ^ v531) + __ROR4__(v538, 27);
	v550 = v536 - 899497514 + v522 + (v541 ^ v529 ^ v538);
	v551 = __ROR4__(v440 ^ v544 ^ v490 ^ v533, 31);

	v556 = v536 - 899497514 + v522 + (v541 ^ v529 ^ v538) + __ROR4__(v548, 27);
	v559 = v545 - 899497514 + v529 + (v546 ^ v541 ^ v548) + __ROR4__(v536 - 899497514 + v522 + (v541 ^ v529 ^ v538) + __ROR4__(v548, 27), 27);
	v565 = __ROR4__(v440 ^ v544 ^ v490 ^ v533, 31) - 899497514 + v541 + (__ROR4__(v548, 2) ^ v546 ^ v556) + __ROR4__(v559, 27);
	v572 = __ROR4__(v448 ^ v432 ^ v498 ^ v536, 31) - 899497514 + v546 + (__ROR4__(v556, 2) ^ __ROR4__(v548, 2) ^ v559) + __ROR4__(v565, 27);
	free(v592);
	*(unsigned int *)result += __ROR4__(v465 ^ v448 ^ v514 ^ __ROR4__(v440 ^ v544 ^ v490 ^ v533, 31), 31) - 899497514 + __ROR4__(v556, 2) + (__ROR4__(v565, 2) ^ __ROR4__(v559, 2) ^ v572) +
		__ROR4__(__ROR4__(v459 ^ v440 ^ v508 ^ v545, 31) - 899497514 + __ROR4__(v548, 2) + (__ROR4__(v559, 2) ^ __ROR4__(v556, 2) ^ v565) + __ROR4__(v572, 27), 27);
	*(unsigned int *)(result + 4) += __ROR4__(v459 ^ v440 ^ v508 ^ v545, 31) - 899497514 + __ROR4__(v548, 2) + (__ROR4__(v559, 2) ^ __ROR4__(v556, 2) ^ v565) + __ROR4__(v572, 27);
	*(unsigned int *)(result + 8) += __ROR4__(v572, 2);
	*(unsigned int *)(result + 12) += __ROR4__(v565, 2);
	*(unsigned int *)(result + 16) += __ROR4__(v559, 2);
	return result;
}




















