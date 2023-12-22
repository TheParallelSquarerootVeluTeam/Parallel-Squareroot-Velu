.intel_syntax noprefix

.section .rodata

.set pbits,1791
.set pbytes,224
.set plimbs,28


.global p
p:
.quad 0x4B2A9EAB4B6B6303,0x1E9C96A175D94B59,0xE4737C3CC3305646,0xD8883D2B79931C19 
.quad 0x4A4F7679F62B0C30,0xF5868A6C22E8455B,0xE658489E1CA359DA,0x1DF44B31DDCDE876 
.quad 0x9E0F4D82FF3FD0EB,0xF7F8206B444A42D3,0x736D3C067C8F2DFD,0xB008E4BA6D26E56C 
.quad 0x2DEC0C2930F8AE51,0x6C104DC99AC9A453,0x203C57A31031B98B,0x14AB11A882AD78B6 
.quad 0x545F5BE025D63BC9,0x54621ADB35B5E4B0,0xA4BB3B200A4E618C,0x96F73F1DDBFEC980 
.quad 0xBD72A3C51844BB01,0x4C101A1DF0D96778,0xDB59CDDDA7876B51,0xEC69843C04DEAEA2 
.quad 0x387DA2DD519C17FB,0x36E72253101645B1,0xD0650FE3AFC04135,0x4FA4E8C57C4EFF02 



.global inv_min_p_mod_r
inv_min_p_mod_r:
.quad 0x71009EB2DDBD6055,0xDE9A176A464E1CA,0xDF424F31ADDDCF1F,0x6820A902009EB498 
.quad 0x4FA40D142FD0EA20,0x9E47BCF7900385F5,0x1CCCAE2F27CB3284,0x56D71883432C86D4 
.quad 0x13FBDD30D7079931,0x3BFA795E60A20853,0xB29117572E1DCA21,0xD37C7D5A4DEE1CF3 
.quad 0xA06EE2406E57AC5E,0xF0BB4F03A30C64C,0x53DE224CE71356DE,0x9B4A32560793F481 
.quad 0xF87E41ECFB8DFB53,0xC077878D8FE4C7C1,0x70CA96A8C5D78A58,0x3AD714F130300F9 
.quad 0x4B579B7B159CC9DD,0xD1402AA08E9C026B,0x3AF4471572D65DD3,0xD49120F9E70A20CE 
.quad 0xBC3305C76F296BB5,0xD35C8FB073908880,0xE462070891C8F4FB,0x8B5D9FA3A23EA7A6 



.global fp_0
fp_0:
.zero pbytes


.global fp_1
fp_1:
.quad 0x1E8023FE1DBDD6F7,0xA42A3C1B9E741DF4,0x52A58B49B66EFD2D,0x7667487D9346ABB2 
.quad 0x21119C921D7EDB6D,0x1F6C60BB97472FEE,0x4CF72625AA15F26F,0xA6231E6A6696469B 
.quad 0x25D2177702408D3E,0x18179EBE33213785,0xA5B84BEC8A527606,0xEFE551D0B88B4FBA 
.quad 0x763BDB846D15F50A,0xBBCF16A32FA31306,0x9F4AF916CF6AD35D,0xC1FECB0677F795DD 
.quad 0x2E1EC5F8E7D4CA4,0x2D9AF6E5EDE51EF,0x11CE4E9FE114DB5B,0x3B1A42A66C03A37E 
.quad 0xC7A814B0B731CEFB,0x1BCFB1A62D73C995,0x6DF296670969BE0C,0x3AC3734BF163F417 
.quad 0x568717680B2BB80C,0x5B4A9906CFBD2EEC,0x8ED0D054F0BF3C60,0x111145AF8B1302F7 



.global r_squared_mod_p 
r_squared_mod_p :
.quad 0xFE005DD827FCEC1C,0x9E77EAB630C13762,0x14747D66DF2302FF,0xC762F012B8992173 
.quad 0xC38CBC38BE0A1245,0x46AF2C4F372D0A8C,0x2DF5213F09254470,0x648905FE4D634C9C 
.quad 0xC6A23929D588CCE6,0x77CCFD243FC5D462,0x1B3F4C4600604F24,0x6C494AC734184771 
.quad 0xEB76777B23432775,0xFC908EAD0E615537,0x3CA23DA079EC89F,0xFB2BB05927446FB 
.quad 0x73E21DBA3951CB7E,0xA615DF86AD10BBB8,0xFE1F3B3C07F12683,0x285EA7FA847C8C00 
.quad 0x93941B06ABDBF928,0xC707D5A1B2869887,0x5E7B5588FC09B98E,0x86AA8F8FE7495009 
.quad 0x53C63B3BD924EB4,0xD9EBF54858FABB07,0x32EA57157D816D09,0xA8DAB00544BDE1 



.global p_minus_2
p_minus_2:
.quad 0x4B2A9EAB4B6B6301,0x1E9C96A175D94B59,0xE4737C3CC3305646,0xD8883D2B79931C19 
.quad 0x4A4F7679F62B0C30,0xF5868A6C22E8455B,0xE658489E1CA359DA,0x1DF44B31DDCDE876 
.quad 0x9E0F4D82FF3FD0EB,0xF7F8206B444A42D3,0x736D3C067C8F2DFD,0xB008E4BA6D26E56C 
.quad 0x2DEC0C2930F8AE51,0x6C104DC99AC9A453,0x203C57A31031B98B,0x14AB11A882AD78B6 
.quad 0x545F5BE025D63BC9,0x54621ADB35B5E4B0,0xA4BB3B200A4E618C,0x96F73F1DDBFEC980 
.quad 0xBD72A3C51844BB01,0x4C101A1DF0D96778,0xDB59CDDDA7876B51,0xEC69843C04DEAEA2 
.quad 0x387DA2DD519C17FB,0x36E72253101645B1,0xD0650FE3AFC04135,0x4FA4E8C57C4EFF02 



.global p_minus_1_halves
p_minus_1_halves:
.quad 0xA5954F55A5B5B181,0xF4E4B50BAECA5AC,0xF239BE1E61982B23,0x6C441E95BCC98E0C 
.quad 0xA527BB3CFB158618,0x7AC34536117422AD,0x732C244F0E51ACED,0x8EFA2598EEE6F43B 
.quad 0xCF07A6C17F9FE875,0xFBFC1035A2252169,0x39B69E033E4796FE,0xD804725D369372B6 
.quad 0x96F60614987C5728,0xB60826E4CD64D229,0x101E2BD18818DCC5,0x8A5588D44156BC5B 
.quad 0x2A2FADF012EB1DE4,0x2A310D6D9ADAF258,0x525D9D90052730C6,0xCB7B9F8EEDFF64C0 
.quad 0x5EB951E28C225D80,0xA6080D0EF86CB3BC,0x6DACE6EED3C3B5A8,0xF634C21E026F5751 
.quad 0x9C3ED16EA8CE0BFD,0x9B739129880B22D8,0x683287F1D7E0209A,0x27D27462BE277F81 



.global p_minus_3_quarters
p_minus_3_quarters:
.quad 0x52CAA7AAD2DAD8C0,0x87A725A85D7652D6,0x791CDF0F30CC1591,0x36220F4ADE64C706 
.quad 0xD293DD9E7D8AC30C,0xBD61A29B08BA1156,0xB99612278728D676,0xC77D12CC77737A1D 
.quad 0xE783D360BFCFF43A,0x7DFE081AD11290B4,0x1CDB4F019F23CB7F,0x6C02392E9B49B95B 
.quad 0xCB7B030A4C3E2B94,0xDB04137266B26914,0x880F15E8C40C6E62,0x452AC46A20AB5E2D 
.quad 0x1517D6F809758EF2,0x151886B6CD6D792C,0x292ECEC802939863,0x65BDCFC776FFB260 
.quad 0x2F5CA8F146112EC0,0x530406877C3659DE,0xB6D6737769E1DAD4,0xFB1A610F0137ABA8 
.quad 0x4E1F68B7546705FE,0x4DB9C894C405916C,0xB41943F8EBF0104D,0x13E93A315F13BFC0 



.section .data

.global fpadd
fpadd:
     .quad 0

.global fpsqr
fpsqr:
     .quad 0

.global fpmul
fpmul:
     .quad 0

.section .text

.p2align 4,,15

.global init_counters
init_counters:
      movq fpadd, 0
      movq fpsqr, 0
      movq fpmul, 0
      ret

.global fp_copy
fp_copy:
    cld
    mov rcx, plimbs
    rep movsq
    ret

.global fp_cswap
fp_cswap:
    movzx rax, dl
    neg rax
    .set k, 0
    .rept plimbs
        mov rcx, [rdi + 8*k]
mov rdx, [rsi + 8*k]
        mov r8, rcx
        xor r8, rdx
        and r8, rax

        xor rcx, r8
        xor rdx, r8

        mov [rdi + 8*k], rcx
        mov [rsi + 8*k], rdx

        .set k, k+1
    .endr
    ret


.global fp_random
fp_random:

    push rdi
    mov rsi, pbytes
    call randombytes
    pop rdi
    mov rax, 1
    shl rax, (pbits % 64)
    dec rax
    and [rdi + pbytes-8], rax

    .set k, plimbs-1
    .rept plimbs
        mov rax, [rip + p + 8*k]
        cmp [rdi + 8*k], rax
        jge fp_random
        jl 0f
        .set k, k-1
    .endr
    0:
    ret