#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define ll short
#define ld float
ll shrt_round(ld num) {
    ll ans = 0;
    asm{
            finit
            fld dword ptr num
            frndint
            fist word ptr ans
    }
    return ans;
}
ld linear_trnsfmtn(ld num, ld rf, ld rr) {
    ld ans = 0;
    asm{
            finit
            fld dword ptr num
            fdiv dword ptr rf
            fmul dword ptr rr
            fstp dword ptr ans
    }
    return ans;
}
void stop(ld* params) {}
ld a_linear(ld arg, ld* params) {
    ld paramA = params[0];
    ld paramB = params[1];
    asm{
      finit
      fld dword ptr arg
      fld dword ptr paramA
      fmulp st(1), st(0)
      fld dword ptr paramB
      fadd st(0), st(1)
      fst dword ptr arg
    }

    return arg;
}
ld a_quadratic(ld arg, ld* params) {
    ld paramA = params[0];
    ld paramB = params[1];
    ld paramC = params[2];
    asm{
      finit
      fld dword ptr arg
      fmul st(0), st(0)
      fld dword ptr paramA

      fmulp st(1), st(0)

      fld dword ptr arg
      fld dword ptr paramB
      fmulp st(1), st(0)

      faddp st(1), st(0)

      fld dword ptr paramC
      fadd st(0), st(1)

      fst dword ptr arg
    }
    return arg;
}
ld power(ld x, ld y) {
    ll cr;
    asm{
      finit
      fstcw word ptr cr
      mov bx,word ptr cr
      or bx, 3072
      mov word ptr cr, bx
      fldcw word ptr cr
      fld dword ptr y
      fld dword ptr x
      fyl2x
      fld st(0)
      frndint
      fsubr st(0), st(1)
      f2xm1
      fld1
      faddp
      fscale
      fxch st(1)
      fstp st
      fst dword ptr x
    }
    return x;
}
ld a_power(ld arg, ld* params) {
    ld paramA = params[0];
    return power(arg, paramA);
}
ld a_exp(ld arg, ld* params) {
    ld paramA = params[0];
    return power(paramA, arg);
}
ld a_log(ld arg, ld* params) {
    ld paramA = params[0];
    asm{
      fld1
      fld dword ptr arg
      fyl2x
      fld1
      fld dword ptr paramA
      fyl2x
      fdivp st(1), st(0)
      fst dword ptr arg
    }
    return arg;
}
typedef ld (*math_function_t)(ld, ld*);
ld input() {
    char *buf = new char[256];
    scanf("%s", buf);
    return strtod(buf, NULL);
}
void plotMode() {
  asm{
	    mov ax, 0013h
	    int 10h
  }
}
void textMode() {
  asm{
	    mov ax,0003h
	    int 10h
  }
}
void plot(ll *array, char color) {
    asm{

	    mov ax, 0A000h
	    mov es, ax
    }
    for (ll i = 0; i < 320; i++) {
	ll j;
	if (i == 0) j = 100 - array[i];
	else j = 100 - array[i-1];
	ll inc;
	if (j >= 100 - array[i]) inc = -1;
	else inc = 1;
	while(((100 - array[i]) - j)*inc > -1){
	  if (j > 200 || j < 0) {
	    j += inc;
	    continue;
	  }
	  asm{
		  mov ax,word ptr j
		  mov dx,320
		  mul dx
		  mov dx, word ptr i
		  add dx,ax
		  mov al, byte ptr color
		  mov di, dx
		  mov[es:di], al
	  }
	  j += inc;
	}
    }
}
int main() {
    ld x_bound = 0;
    ld y_bound = 0;
    ld *params = new ld[3];
    ll func[320];
    math_function_t math_function;
    do{
    clrscr();
    char menu[] = {
	    "Choose:\n"
        "\t0. To exit\n"\
	    "\t1. Linear (y = ax + b)\n"\
	    "\t2. Quadratic (y = ax^2 + bx + c)\n" \
	    "\t3. Power (y = x^a)\n" \
	    "\t4. Exponential (y = a^x)\n"
    };
    printf("%s", menu);
    ll func_num = -1;
    while (func_num < 0 || func_num > 4) {
        char *buf = new char[256];
        scanf("%s", buf);
        func_num = strtol(buf, NULL, 10);
    }
    if(func_num == 0)
    return 0;
    x_bound = 0;
    y_bound = 0;
    printf("Enter a positive X bound: ");
    while (x_bound <= 0)
	x_bound = input();
    printf("Enter a positive Y bound: ");
    while (y_bound <= 0)
	y_bound = input();
    clrscr();
    printf("\tOx(0, %.1f), Oy(0, %.1f)\n", x_bound, y_bound);
    switch (func_num) {
    case 0:
        exit(0);
	case 1:
	    printf("\ty = ax + b\nEnter the A parameter: ");
	    params[0] = input();
	    printf("Enter the B parameter: ");
	    params[1] = input();
	    math_function = a_linear;
	    break;
	case 2:
	    printf("\ty = ax^2 + bx + c\nEnter the A parameter: ");
	    params[0] = input();
	    printf("Enter the B parameter: ");
	    params[1] = input();
	    printf("Enter the C parameter: ");
	    params[2] = input();
	    math_function = a_quadratic;
	    break;
	case 3:
	    printf("\ty = x^a\nEnter the A parameter: ");
	    params[0] = input();
	    math_function = a_power;
	    break;
	case 4:
	    printf("\ty = a^x\nEnter the A parameter: ");
	    params[0] = input();
	    math_function = a_exp;
	    break;
	default:
	    exit(0);
    }
    ll originX[320] = {0};
    ld funcArea = 0;
    ld fDelta = linear_trnsfmtn(1, 999, x_bound) - linear_trnsfmtn(0, 999, x_bound);
    for (ld i = 0; i < 999; i += 1) {
      ld arg_1 = linear_trnsfmtn(i, 999, x_bound);
      ld arg_2 = linear_trnsfmtn(i+1, 999, x_bound);
      ld val_1 = math_function(arg_1, params);
      ld val_2 = math_function(arg_2, params);
      ld contTwo = 2;
      asm{
          finit
          fld dword ptr val_1
          fabs
          fld dword ptr val_2
          fabs
          faddp st(1), st(0)
          fld dword ptr contTwo
          fdivp st(1), st(0)
          fld dword ptr fDelta
          fmulp st(1), st(0)
          fld dword ptr funcArea
          faddp st(1), st(0)
          fst dword ptr funcArea
      }
    }
    plotMode();
    plot(originX, 26);
    for (i = 0; i < 320; i += 1) {
	ld arg = linear_trnsfmtn(i, 319, x_bound);
	ld val = math_function(arg, params);
	func[i] = shrt_round(linear_trnsfmtn(val, y_bound, 99));
    }
    plot(func, 128);
    getch();
    textMode();
    printf("Area of function: %.3f\n", funcArea);
    switch (func_num) {
    case 1:
        printf("\ty = ax + b\nEnter the A parameter: ");
        params[0] = input();
        printf("Enter the B parameter: ");
        params[1] = input();
        math_function = a_linear;
        printf("Enter the X parameter: ");
        ld argg1 = input();
        argg1 = a_linear(argg1, params);
        printf("The value of the function at the point: %.3f\n", argg1);
        break;
    case 2:
        printf("\ty = ax^2 + bx + c\nEnter the A parameter: ");
        params[0] = input();
        printf("Enter the B parameter: ");
        params[1] = input();
        printf("Enter the C parameter: ");
        params[2] = input();
        math_function = a_quadratic;
        printf("Enter the X parameter: ");
        ld argg2 = input();
        argg2 = a_quadratic(argg2, params);
        printf("The value of the function at the point: %.3f\n", argg2);
        break;
    case 3:
        printf("\ty = x^a\nEnter the A parameter: ");
        params[0] = input();
        math_function = a_power;
        printf("Enter the X parameter: ");
        ld argg3 = input();
        argg3 = a_power(argg3, params);
        printf("The value of the function at the point: %.3f\n", argg3);
        break;
    case 4:
        printf("\ty = a^x\nEnter the A parameter: ");
        params[0] = input();
        math_function = a_exp;
        printf("Enter the X parameter: ");
        ld argg4 = input();
        argg4 = a_exp(argg4, params);
        printf("The value of the function at the point: %.3f\n", argg4);
        break;
    default:
        exit(0);
    }
    printf("\nPress any button", funcArea);
    }while(getch() != 'F');
    return 0;
}