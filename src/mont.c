#include "mont.h"
#define _MONT_C_CODE_
#include "sdacs.h"
#include "ijk.h"

/* All the projective curve coefficients corresponds with (A + 2C : 4C) */

// Affine Montgomery coefficient computation (A + 2C : 4C) --> A/C
void coeff(fp B, proj const A)
{
	fp t;
	fp_add(t, A[0], A[0]);	// (2 * A24)
	fp_sub(t, t, A[1]);	// (2 * A24) - C24

	fp_copy(B, A[1]);
	fp_inv(B);		// 1 / (C24)
	fp_add(t, t, t);	// 4*A = 2[(2 * A24) - C24]
	fp_mul(B, t, B);	// A/C = 2[(2 * A24) - C24] / C24
}

// Differential point doubling
void xdbl(proj Q, const proj P, proj const A)
{
	fp t_0, t_1;
	fp_sub(t_0, P[0],P[1]);
	fp_add(t_1, P[0],P[1]);

	fp_sqr(t_0, t_0);
	fp_sqr(t_1, t_1);

	fp_mul(Q[1], A[1], t_0);
	fp_mul(Q[0], Q[1], t_1);

	fp_sub(t_1, t_1, t_0);
	fp_mul(t_0, A[0], t_1);
	fp_add(Q[1], Q[1], t_0);
	fp_mul(Q[1], Q[1], t_1);
}

// Differential point addition
void xadd(proj R, const proj P, proj const Q, proj const PQ)
{
	fp a, b, c, d;

	fp_add(a, P[0], P[1]);
	fp_sub(b, P[0], P[1]);
	fp_add(c, Q[0], Q[1]);
	fp_sub(d, Q[0], Q[1]);

	fp_mul(a, a, d);
	fp_mul(b, b, c);
	fp_add(c, a, b);
	fp_sub(d, a, b);

	fp_sqr(c, c);
	fp_sqr(d, d);

	fp_mul(R[0], PQ[1], c);
	fp_mul(R[1], PQ[0], d);
}

// Differential point multiplication by l_i, that is, x([l_i]P)
void xmul(proj Q, uint64_t const i, proj const P, proj const A)
{
	proj R0, R1, R2, T;
	proj_copy(R0, P);
	xdbl(R1, P, A);
	xadd(R2, (const fp*)R1, (const fp*)R0, P);

	int j;
	for (j = LENGTHS[i] - 1; j >= 0; j--)
	{
		proj_cswap(R0, R1, (uint8_t)((int)SDACs[i][j] - 48));	// cswap of points
		// This branch is only required for CSIDH
		// It would amazing to do the next branch with constant-swaps (xdbl can be easily modified in order to have the same cost than xadd)
		if (isinfinity((const fp*)R0))
			xdbl(T, (const fp*)R2, A);
		else
			xadd(T, (const fp*)R2, (const fp*)R1, (const fp*)R0);

		proj_copy(R0, (const fp*)R1);
		proj_copy(R1, (const fp*)R2);
		proj_copy(R2, (const fp*)T);
	};

	proj_copy(Q, (const fp*)R2);
}

// Elligator is used for sampling point on E(fp)[\pi - 1] and E(fp)[\pi + 1]
void elligator2(proj Tp, proj Tm, proj const A)
{
	
	#if defined(P512) || defined(Ptest)
		fp u;
		fp_random(u);   
	#endif
	
	#ifdef P1024
	fp u = {0xc58ad041675af56c,0x4a3b991472316fae,0x62df3dca8d1a1680,0xda6b9da1c4a6356b,0x8dede7ea30d2571,0x9566f26b38cd071b,0x4f9b0ec9c7232c3f,0x91f25963952f1652,0xb90c2305dc1f1e28,0x66db495bdb49f054,0x232a951234779993,0xb1418034744d7a1f,0x28339c29aeec21d5,0xeabe9a9fa1233ca3,0xc3b328cd02f5408a,0x8e2226c79ac571b};
	#endif
	#ifdef P1792
	fp u = {0x94f717c9c192f2c3,0x41ec8aa51d18702f,0x9c6018df9f1114ff,0xc3418c0b5801fe88,0x6c37fd2c5bf0d432,0xc4fffd42e717fb92,0x5ca4b89ba89a4298,0x8aa8056504e9594c,0xa539ac77e5dd584b,0xea24214cf7648bd1,0xcfa17263f036e7f9,0xfc14220494416127,0xa25480f43a2911a6,0x60df4d9798395ca6,0x8d4b47720d5490d8,0x90210ded21af989f,0xf6dd618fd6971112,0xbece65e3c9a23739,0xe724949d1027b34b,0x3bbe160481dc3d7b,0x28879208006b833b,0xbbdae58d993c08b3,0xc816e386ff0cd73a,0x9043692973601e10,0xe65f9ba73be34952,0x4b8e68a6e466bd7,0x29a5cbf7847d8370,0x1f12777095751834};
	#endif
	#ifdef P2048
	fp u = {0x30fdccf5f59aab81,0x2b422c3591081986,0xc972d16be4761285,0x54625779d9f4ee6a,0x77804a49cb287815,0xa38af2447259f1e0,0x6c9cad7b0452c892,0xc9365e4ee5db6c49,0x6f0771845c00df63,0x4a8faed41b38fb81,0xbcf932db10897d77,0x211801c957319b2b,0xe4c3f3ad3d6dd4e9,0xf78cd4591bf138c7,0xcb1e2006c7af6b66,0x8df26b45f52894c5,0xbf8908c7927a8e61,0xb81c8c1d9ccaa52e,0xd8feca7451617f8f,0xcc8a700b66d5b60a,0x8db91b8878be7daa,0xa18f5ea9fb33a94a,0xfb07f9b62fd2c84b,0xc6d1132913cc4e33,0xed05de753f26845d,0xebe170d8e04da4df,0xf27a1a84ada15c58,0x358698277219a988,0x400fa52a253e4d71,0x8c533678e8244cad,0x135fb547e9173e35,0x10e96f4817ae0c6};
	#endif
	#ifdef P3072
	fp u = {0xa7b110a9e2b3a1a9,0x5c3e91472f45559e,0x26b21da565b848c,0xaf60e423adb21f9e,0x73971921bf1f185a,0xe8ab6f09861adbb7,0x9cf0587722d63a64,0xc03ff3fa58fb7b50,0xc385ac9e3eece4,0x9913f441efa3aac4,0x5063bbbea2d617fe,0xa66c5d2f616c2e15,0x14b66488dc284348,0xb593518f07c4c684,0x6e4ecbc99fd135f7,0xaaf6d0e963b686b0,0xfa12e92ee137492,0x690a9238ad900903,0x4931dbc6882669e6,0xc8bbae306007a027,0x4eb22d481cdcb99,0x5594409f8c275785,0x70aca786be36ae07,0x8e9976e7c06fc1d,0x365812f278385aa2,0x9ea044558a1f4287,0x31a63fda35b3a946,0x9c3cfbdff6fbaf46,0xe9a121972a5855b6,0x3629ac3052f42424,0xe80e3c46399fee48,0xbae4bb4327c3384d,0x84feab003fff4183,0x380e6d2f5afb49b,0x384d9fd888ab8142,0x98384c0ff8e47cc1,0x39ff2d0cc303a711,0x3897ed08815ef64f,0x652d007ba4d1fa96,0xbd46b385a83a9b32,0x509c9c66d7b4ab56,0x9575e16d18c9b659,0xe672093cf427eaba,0x6cd6f026a0495b13,0xcd8b3b3e0e26096d,0xd536c24a32fdfa58,0x773b3d953e587d95,0x22c75d4d2ca2e8d3};
	#endif
	#ifdef P4096
	fp u = {0x87daa4ceb460f3aa,0xaf1799d5a2139e86,0xbe2e0f2dd98fc7d7,0x7ebd7e4001f68755,0x8b758735f0f7b09b,0xcce30b60e5e8e9ec,0x54a52895090e7a78,0x327088335fbb71c,0xcf827f95c56014bb,0xae5340dfa0d8078a,0x2314e767ec2e4f73,0x67823e8f3c39e10c,0x2fb9b58d3af5175f,0xf9cfa0d2c5f2f854,0xb546a3ad1279fe74,0x502766988a44450e,0x225883f26c767a8d,0x4964b6a3b3789fd7,0x633f6f8a75a48c7d,0xfa7949bab00d1861,0xc71be59c37ba5e81,0x584f80c9636f64b8,0x424e60b9c8b9ce7c,0x6ccf1415a3655348,0xbc62f05302d18913,0x87b33313cd493d2d,0x82fdb5931b4a0861,0x2701ffecd3065ef1,0x6554e1be4f1f13c0,0xd8b3e242e8b96a25,0x50cb2a29c478af58,0xaf8d7fc94eeb240a,0xbcbc49055f5268c3,0xfe1ff98e6cb8485d,0x21865b6df437cf86,0x55b52089d7166f09,0xe9cfdbafb5f6b946,0xc045d5b0e3715477,0xb091987bdf3ca9b9,0x35f642089b5abcd0,0x932f40172a295273,0x56e7efdc036b61bf,0xf51afe2ddc2bce20,0xc9ede5c2608c1180,0x2948e06259e90636,0x12a749f55dd4fe24,0x21304512282c67e5,0xdb288fd05c5a11e,0x9c280e72b75d0398,0xb9096917f89b9b42,0x3071ac7765a7b952,0xd270112758fb1c57,0x606e1401b4b212e6,0xd5f4751a8ada6f85,0xc74c56bc9d68cf25,0xecd60bb9eb1e2f38,0x1ee7b182fe011557,0x2b0c40277671ac9f,0x2bad44df0a922e4b,0xdd55c564412ba9e3,0x3ca22a4c18346cf8,0xdb31400dfd7ff2af,0x8ab7aec2937aca04,0x4a4268d6bae57df5};
	#endif
	#ifdef P5120
	fp u = {0xe7b1ed289752eae2,0x61cdc7143dc90aa9,0xad5676610d49eed9,0xe87e36858b31fb2b,0x3a81d0375b9801db,0x527c0a8f2a29741d,0x8bd41f54ecb39f62,0x70d13edb2332a3ed,0x70eda72beeff3273,0x4eb667f5c3c0f78c,0xe664b5b0e4437a9d,0x50bfe0e3f5226d8,0x27d09d4d9cff3e8f,0xe4060eadcf8e6fc1,0x203d3110bfb46c37,0xda0a5439787ef8d1,0x5ecd7305e7f48b3,0x89e03a6be9428725,0x130706855c3cb505,0xc51145b721dde6ca,0x5e9ad6f7a45ada1e,0xb9f4bd8d394d7c03,0x9c3faa9658b28c32,0x6e091f26e3c9a47e,0x53b33d941de0f024,0xfbaeab213c54ca41,0x30109386130fbb73,0x5728b26092eee877,0x6bfbb7f1f354edf3,0xe362b7a9ca01bb19,0x2648fc2ccfc9d236,0xc78806b9e2638b65,0x7b2e3bcf01dd83d4,0x6038d65b77057f50,0x257c83189796b425,0x793950ee5a9c1345,0x7bc3585c1ff8f7f2,0xa5e7ae69c251ccd7,0xd7bf75f5d7ef6ee,0x4a56a854d9361cf3,0xe224f3f802bc7c06,0xe720c709ff47bd33,0xc4051f0f14800821,0xae4155055aa9aded,0x37793fa48b6394e4,0x279765490f02145b,0x398ebbb5ff8c82a7,0x12b18a54e66035b2,0xf612e0475b979e00,0xaa8267f9c74bba1c,0x5473768a10201781,0x543cbbe659b01534,0x8b39fc17a5af204b,0x7a08b83a9464ff11,0xb124ba1431661c7e,0x63247876a4bd30a2,0xbc7d5c0eedef2e01,0x4d05e8fb40767e88,0x8a1bc0566bc711a2,0x7b949ca40a6bf4b4,0xc5e28cdce85e5d11,0x535e08d5034c03db,0xcdeb2736046e78a1,0x2827c5ef3bacc91c,0x3bd406de621c046f,0xfb63c15407c54ff,0xd86cea00421ca235,0x563d000cbf70e136,0xef7879d86a160887,0xe8b5b7c5e1080745,0xcf49e37dd9fd5fee,0x90bab6de093df706,0x4ea89c2fa6546405,0xdcf9190520432a11,0xb9c0970ef9e24291,0x45be491fd0368f3,0x8d2ffe2003a008d8,0xea34fc1bd935b79b,0xea8bb0383e3656f3,0x142323ec1ca1a36b};
	#endif
	#ifdef P6144
	fp u = {0x1367bc672b859435,0x1aca4c3185da5f9c,0x2c6a556a904736cf,0xeea6c608dfdfb466,0x22e407699033e678,0x2a90f4891ab37ca3,0xdec00fbd1dc1c2a0,0x22bd5749e633e5e8,0xc579790b61daf89c,0x9cee08c9166519e1,0xcd44e206eba82d12,0xe382a2bdc3bc877c,0x58b377d603d808ff,0x21df93c866087d84,0xf77c14a93379df9c,0x9862df48d64c40d1,0x27529501b6a37d95,0xddccfe26d9df3d95,0x64082bbcf8f33e6,0x9fab4c267a183d16,0x66523c9e06f2a8b2,0x2a7108621bdf9224,0x110f3156f623072e,0x655edffff677caa5,0x21c96d741d6a620e,0x2873858e1cda3ef3,0x48144ef7a86fad04,0x5ccc0ca4012a6c39,0xe4f74f51623cff3e,0xa5c82b4ed4b5d674,0x71b5deaba5b764e8,0x93135116702222f3,0x600f94b3bc962a34,0x7cdec60f634e569f,0x240d56c616ebd733,0x7c6e4f7ce9127468,0xbb50cdd5d4ae7959,0x1f82f6be893f9b69,0x3760ece60d488b00,0xdc1d62c9a941806a,0x1f33bf786100c847,0xdb884f16fa302733,0x240b87d9463aa168,0x7430de944dc5abac,0x67a1d0f9d0547389,0xd96be74bd05b4ad7,0x1f58ef4340abe85,0x58de668458168109,0x11365c383dcd94bf,0xf8673b66eefe4344,0x3c4b83eab1c7b6e5,0x6bdda14d65998024,0x2f79af928494d84d,0xa4f2011b84757a7e,0x6334b295e4a23ccb,0x4b5c5d7325acb04b,0xee85f6f7d3fa8b42,0x8eeabd1593dbfeb9,0xfc440635eb8320b1,0x38b24c9b746d25f8,0xfaa3a31cf6f856bd,0xe825264df28da885,0x9460fd5b483acba3,0x140d9ffaf1839d0e,0x165d429a8ab04a66,0x993fb45d283982c,0xffe3a89743d5526f,0x81d7b4a0c6615d3c,0x9dfce9e502ba0b38,0xb3e58a80d12a32e7,0x166a1d1f9031b1a0,0xe8786d0ed9c74394,0x6e21bc54bae36e53,0x3be1e0228e92023a,0x9e61d2207eec68a2,0x188c444681ca0fa8,0xc37c29b65df26ae,0x40616b0848030ba9,0xd87abdc326a105f2,0xd1fbedf2ebc2e69a,0x1df25c44c404b4d2,0x4c23d24dc038070e,0x3bc5070cb4ec133f,0x71b232d540472253,0x3c57ec4b5b813430,0x2ee3d4c5f76bace3,0x2b5e0256a55420fc,0xfad0377ae245a7b8,0x2e6fd476cc7b27f0,0x7f376fde86fe73fe,0x1561e3e3128c0c07,0x8a461c0a7b9c3ed8,0xff1da5405deaf6a3,0xb151ab3b71cccdd1,0x90748db277ba7e9e,0x26d5bf67ba4d6364};
	#endif
	#ifdef P8192
	fp u = {0x8d3a91db2a677e06,0x139fd2fc2e343365,0x9e6b5dd6c48b4244,0xacce6e304e957488,0x7d375d500d3f3f45,0x717db00f0b4a5b57,0x1e42c6e044eabdab,0x685ca2faaab6a432,0x30a77cca29873016,0xd1297e26c7e145bb,0xf5da75389c7ea95d,0x2d97a2c20d6f7e55,0x853600508e65cc1d,0x129942fb47a841fd,0x61d12abf4199c2df,0x8025aafacc50a722,0xf1be8cdc32c232bb,0x9b4a7b8bb96b8120,0xc3f4de09125511fe,0x874704172f36914,0x9a0b0e2124cf2159,0xb0c1d866adacbe44,0xa3c707267ca38c95,0x7dac9116cc62a8bd,0xb31af9bd023068f9,0x62bb2a0456c438e7,0xe2e91682829bdb9e,0xb7fbf226d4d9f9de,0x3745c03c1afa8a6,0xd17d2ba2b7aeaabd,0xdd703f0d03e15d25,0x56664da193b4f8a2,0x29964919fcc3696e,0xb0ba43ef88fd7320,0xc4a4603ef92b68b8,0x5f90a16205ae09d1,0x9cf621c17fdebb4,0x1172392104912242,0x6fd50fa9f2776334,0x2c59e3c806fcb959,0xf1e54b52144e1b4,0xd858d64ff39d4cf3,0x1588f5e6b13d78a7,0x74c6006479d1fd9,0x45f04d2c2d70227c,0x760bb9f1536dab5a,0x571d5a2b99f4c40e,0xd47aff9e44627f6e,0x5fcae148ecd5773a,0xa9c4262c86fa8172,0xd7f59a1e2dcf6988,0xb0919dd5827b22c1,0x2fbb0a3550364975,0x9c2d04763a1201e,0xe92de0532c88d276,0x151f419fdf3ea527,0xa876c2d5d286ad5a,0x6c4d9c87d3d4e7f8,0x9e142fa7e00d467e,0xb536bd58112c26c5,0xd31a645efad44045,0x3f235469b9ac57a3,0x4c929b29aef8108a,0x15eed2a609c29074,0x3f269bed0b5c8483,0x59344f5cd350f74a,0xe7795f68d856487,0xaa706eb6da22f1a1,0x114d848166caf8f7,0x7d1614533489e14a,0xbab726f1bb72401d,0xe2e88b996f0cc499,0x7929865df619ec7,0x86f86f64e7f43afd,0xa560bce60f1c5b4a,0x383815b01cfa3517,0xde2d1c35c4c2d123,0x288d2eb04707b407,0x7493f58700dbc6d0,0xe729f4cd6d81174,0xb05f07db30773bf6,0x5692b32170268e0,0x976a9f672057cad7,0xe1ff83e70b1d50a8,0x4d345c2605c4804d,0xed54d759de78b0a9,0x6fe14c2cae0f42ed,0x1ce60357a991d1ce,0xab1372b674d6e75b,0x6c368c7bf84e06b5,0xb7e99077255ecef4,0xdf7f4b40d29a90ec,0xb46cc1a3e593fa90,0x975bd738eb093dcc,0x73e531e6fc00536,0xc7c4fea95b96f01a,0xf68ac4e0ce56873c,0x8649e82fd9050a72,0xd00dcf5b2c9ebbed,0xfda3944b7f75144b,0x75c3caee22fe5214,0xeb10bd3b87b354b3,0x5fab0fafc9bfb115,0x1cb0eb4c33c7e1f6,0xd7ca8ac58663c3d2,0x163a3c64f2cf7e2c,0x1749f6b20d3f20b9,0xc8df7361220b15e3,0x7a7770d974c9f0ec,0x58c9e60e6a6f83fc,0x7d2d97c7d305d317,0x21a21c59e28f90fc,0x6d05998fcdcfe90c,0x25e102c8e0319c68,0xfb1db74d41ae5caf,0xc6dd68ecec0b59b5,0x2bc964c8122debdb,0xdb78ae4580cdc32d,0x16f6dec8badd30b4,0xbcc83ab2304963e4,0x69bf0bebd939de7f,0xf61c7433139d0165,0xae750474dc6f4249,0xd1c61c5600954271,0xe110acc8de346dcc,0x88bbfc669ccb9c89,0x49c633a67fd324a,0x5640f5df21a9bcd1};
	#endif
	#ifdef P9216
	fp u = { 0x4797c4cff8eb9ad8,0x2d8539cba1635248,0xa5bc87ad5f083695,0xbf6bf1822928fc65,0xdc318c8caca87851,0x3c29706ec7605131,0x54b321800ca8d890,0x707ed14ae0610935,0x6a8dcb68c2b5327d,0xa13bc6465e2ad5a9,0x4132e6cf3b2eeb74,0x8831c143b57970ec,0x304e324125ea630c,0xe2baa5e2d9f2ddcb,0x936adfb037f82ab8,0xdbd8f0c3273d5747,0xb0b0542884a4f315,0xc992a56cd914a9f3,0x718ea46f524f71d8,0x1107d8a78aed2bff,0xf029e7dc5d91221a,0x7226a9393d45bf46,0xfb08a4c553a54d69,0xa0fc40919c98061b,0xcdc953e4a23c4185,0xeda85cd09dfd5983,0x8a10001838092f82,0x799e2e9458e04dbb,0x4e4ff0a1c71b2351,0x42d5409efe9f27b,0x1d23c3cdad0ffda,0xc31aeb02b50c8a73,0x1e8bddeab61a0ae2,0x862a8498ea2241dd,0xbd4e7b18e6fc67b5,0xb8eb593c91f42a2e,0xaa3aead90901d791,0x48c145bcc37c055d,0x71e1aa669f54c38f,0xe7a7708f948fcfca,0x9ec2f9ee1059ef2f,0xad2b520c41ef25e4,0xf60c87fddff50aa6,0x9481e4be637c1a47,0x9e055bb342fdb92b,0x8d77553f5807f284,0x75ce46d701c135eb,0x1290a2bf7f4f834a,0x526cc273c25a2088,0xd29044624c278dd0,0x6153087e8bbec6c7,0x97d8b6f98d737b1c,0xbbbbfa7ccc3fbd3,0x10bca82fb20b2087,0xd0d4bd480fe55801,0x84acb51a78cc1a0a,0x96aad35c85850255,0xa95c5c0ed9cc70aa,0xfcb9f7c684e88db0,0x6cdad1f673fd405e,0xab435ba3a022291,0x86bf8302814993eb,0x77da4247bcb6d390,0x3ef46d65dfff499d,0x4a4606c76c6b5fb2,0x92281bfc596dde80,0x69f8f2be0629bb46,0x3204b8f76e394c4f,0xf016d4a428338bff,0xb457e8f903e904f2,0x993b21bbb9a7d36c,0x913f5c80fedb8ffe,0x59c3bc43037de102,0x2ec32f19aad5ce82,0x4b9694ac574c7d6,0x766b86c471b1c44b,0x54dc30ab68c256ba,0x5b55e604bc2e4566,0x93baab48fd8d4569,0x2b56db444d0268f6,0x1aa75bc5ac5aa22e,0x5c051bab46362aa6,0xea7a9298dc934c34,0x1679d1b237765b8c,0x577e4a8a11aa62d0,0x3db8729ab07bbaa0,0x45e2988597384b58,0x29358842010e3160,0x6d825e77bed0ef9a,0x9d9fa0c99217533a,0xa9dc25884eb497fa,0x493fa1c8178dc364,0x1a184c24807ed816,0xad5bac9fb89e2cec,0x435affca640c3f87,0xfd72089b12269ba,0x65623a6a2b4cbb14,0x91e1e145dfefcbfc,0xaf27b5b2a9cf8cd8,0xaa23114dca4d2e8c,0xcd86fbdd39a12e4,0xebee57f79c3e0d3e,0x1935978206fd6f65,0x5870e21618bb418a,0xcac3384f4b6d71ce,0xf194262b73cac760,0x7f33e42dcfee5d83,0xcf21b90668b516d1,0x5648a6db4d9a7336,0xbebcd83e0f4ea91,0x6962d06f2d5a340e,0x7d297ed08412b1d7,0x615c7d968a08e6bb,0xddcf6299db80a5e0,0xf112770507f5c2f3,0x887b28025e71a347,0xaf9b52e66893c4ab,0x2fb74b2db979e3ff,0xd4fa10e33f309c67,0xdaabe7ec3e653fc4,0xdad05535d7957961,0xcdf1cff86e8d3499,0xbb5976ac97fb6c13,0x8d71d1a90735d2ae,0xb403d4c6621e5195,0x84956d64302b8427,0x69858375d7af6b4,0x1324718f6cd0cbc1,0x66bf7bfa9c60ad2e,0x89cd4ed88c769194,0x2dea39fe31f7a093,0x87551d484de92c5a,0x4a2720ecdf91f18b,0x4f938da0768409be,0xcba538294beb635f,0x399855bccd8a1eac,0x30805ee04cf425f2,0xdc0eb57c864782ea,0xde45778e61b587ff,0xc744a6ac2bb5a7d,0x767b8dff6ad838a4,0x6a3519bba8991d54,0x85050b06f77f2f97,0x18c85f35020f229};
	#endif
	


	fp Ap, C_times_u_squared_minus_one, AC_times_u_squared_minus_one,
	u_squared, u_squared_plus_one, u_squared_minus_one,
	   alpha, beta, tmp, aux;

	fp_add(Ap, A[0], A[0]);
	fp_sub(Ap, Ap, A[1]);
	fp_add(Ap, Ap, Ap);


	fp_sqr(u_squared, u);

	fp_add(u_squared_plus_one, u_squared, fp_1);
	fp_sub(u_squared_minus_one, u_squared, fp_1);

	fp_mul(C_times_u_squared_minus_one, A[1], u_squared_minus_one);
	fp_mul(AC_times_u_squared_minus_one, Ap, C_times_u_squared_minus_one);

	fp_sqr(tmp, Ap);
	fp_mul(tmp, tmp, u_squared);
	fp_sqr(aux, C_times_u_squared_minus_one);
	fp_add(tmp, tmp, aux);
	fp_mul(tmp, AC_times_u_squared_minus_one, tmp);

	fp_set0(alpha);
	fp_copy(beta, u);
    	fp_cswap(alpha, beta, fp_iszero(tmp));
	fp_mul(u_squared_plus_one, alpha, u_squared_plus_one);
	fp_mul(alpha, alpha, C_times_u_squared_minus_one);

	fp_add(Tp[0], Ap, alpha);
	fp_mul(Tm[0], Ap, u_squared);
	fp_add(Tm[0], Tm[0], alpha);
	fp_sub(Tm[0], fp_0, Tm[0]);

	fp_add(tmp, tmp, u_squared_plus_one);
	fp_cswap(Tp[0], Tm[0], 1 - fp_issquare(tmp));

	fp_copy(Tp[1], C_times_u_squared_minus_one);
	fp_copy(Tm[1], C_times_u_squared_minus_one);
}



// Elligator is used for sampling point on E(fp)[\pi - 1] and E(fp)[\pi + 1]
void elligator(proj Tp, proj Tm, proj const A)
{
	



	fp Ap, C_times_u_squared_minus_one, AC_times_u_squared_minus_one,
	   u, u_squared, u_squared_plus_one, u_squared_minus_one,
	   alpha, beta, tmp, aux;

	fp_add(Ap, A[0], A[0]);
	fp_sub(Ap, Ap, A[1]);
	fp_add(Ap, Ap, Ap);

	fp_random(u);
	fp_sqr(u_squared, u);

	fp_add(u_squared_plus_one, u_squared, fp_1);
	fp_sub(u_squared_minus_one, u_squared, fp_1);

	fp_mul(C_times_u_squared_minus_one, A[1], u_squared_minus_one);
	fp_mul(AC_times_u_squared_minus_one, Ap, C_times_u_squared_minus_one);

	fp_sqr(tmp, Ap);
	fp_mul(tmp, tmp, u_squared);
	fp_sqr(aux, C_times_u_squared_minus_one);
	fp_add(tmp, tmp, aux);
	fp_mul(tmp, AC_times_u_squared_minus_one, tmp);

	fp_set0(alpha);
	fp_copy(beta, u);
    	fp_cswap(alpha, beta, fp_iszero(tmp));
	fp_mul(u_squared_plus_one, alpha, u_squared_plus_one);
	fp_mul(alpha, alpha, C_times_u_squared_minus_one);

	fp_add(Tp[0], Ap, alpha);
	fp_mul(Tm[0], Ap, u_squared);
	fp_add(Tm[0], Tm[0], alpha);
	fp_sub(Tm[0], fp_0, Tm[0]);

	fp_add(tmp, tmp, u_squared_plus_one);
	fp_cswap(Tp[0], Tm[0], 1 - fp_issquare(tmp));

	fp_copy(Tp[1], C_times_u_squared_minus_one);
	fp_copy(Tm[1], C_times_u_squared_minus_one);
}

// For computing [(p + 1) / l_i]P, i:=0, ..., (N - 1)
void cofactor_multiples(proj P[], proj const A, size_t lower, size_t upper)
{
	assert(lower < upper);
	if (upper - lower == 1)
		return ;

	int i;
	size_t mid = lower + (upper - lower + 1) / 2;

	proj_copy(P[mid], (const fp*)P[lower]);
	for (i = lower; i < (int)mid; i++)
		xmul(P[mid], i, (const fp*)P[mid], A);

	for (i = (int)mid; i < (int)upper; i++)
		xmul(P[lower], i, (const fp*)P[lower], A);

	cofactor_multiples(P, A, lower, mid);
	cofactor_multiples(P, A, mid, upper);
}

// Next functions determines is the Montgomery curve y² = x³ + ax² + x is supersingular
bool validate(fp const a)
{
	init_counters();	// set to zero the field operation counters
	fp x;
	proj A, P[N];
	// A = (a : 1)
	fp_copy(A[0], a);
	fp_set1(A[1]);

	// Coding curve coefficients as (A' + 2C : 4C)
	fp_add(A[1], A[1], A[1]);	// 2C
	fp_add(A[0], A[0], A[1]);	// A' + 2C
	fp_add(A[1], A[1], A[1]);	// 4C

	int i;
	uint64_t bits;

	do
	{
		bits = 0;
		// P = (x : 1)
		fp_random(x);
		fp_copy(P[0][0], x);
		fp_set1(P[0][1]);

		// Multiplying by 2^cofactor
		for (i = 0; i < (int)cofactor; i++)
			xdbl(P[0], (const fp*)P[0], (const fp*)A);
		
		// At this step, P[0] is expected to be a torsion-([p + 1]/[2^e]) point
		cofactor_multiples(P, (const fp*)A, 0, N);
		for (i = N - 1; i >= 0; i--)
		{
			// we only gain information if [(p+1)/l] P is non-zero
			if (isinfinity((const fp*)P[i]) != 1)
			{
				xmul(P[i], i, (const fp*)P[i], (const fp*)A);

				// P does not have order dividing p + 1?
				if (isinfinity((const fp*)P[i]) != 1)
					return false;

				// If bits > UPPER_BOUND, hence definitely supersingular
				bits += bL[i];
				if (bits > UPPER_BOUND)
					return true;
			};
		};

	} while (1);
}


