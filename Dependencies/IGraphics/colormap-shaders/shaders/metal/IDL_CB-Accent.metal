#include <metal_stdlib>
using namespace metal;

namespace colormap {
namespace IDL {
namespace CB_Accent {

float colormap_red(float x) {
	if (x < 0.3953623640294495) {
		return 4.43904418116747E+02 * x + 1.27235098111810E+02; // R1
	} else if (x < 0.5707952559161218) {
		return -1.40693770913775E+03 * x + 8.58988416988442E+02; // R2
	} else if (x < 0.7167119613307117) {
		return 1.26199099099112E+03 * x - 6.64423423423499E+02; // R3
	} else if (x < 0.8579249381242428) {
		return -3.45591749644313E+02 * x + 4.87750355618723E+02; // R4
	} else {
		return -6.12161344537705E+02 * x + 7.16447058823441E+02; // R5
	}
}

float colormap_green(float x) {
	if (x < 0.1411385125927322) {
		return -1.90229018492177E+02 * x + 2.01102418207681E+02; // G1
	} else if (x < 0.2839213365162221) {
		return 1.26397818871505E+02 * x + 1.56414177335230E+02; // G2
	} else if (x < 0.4292115788900552) {
		return 4.30655855855847E+02 * x + 7.00288288288335E+01; // G3
	} else if (x < 0.5716859888719092) {
		return -1.03353736732686E+03 * x + 6.98477513951204E+02; // G4
	} else if (x < 0.7167535225418249) {
		return -7.29556302521079E+02 * x + 5.24695798319375E+02; // G5
	} else if (x < 0.8577494771113141) {
		return 6.31469498069341E+02 * x - 4.50824238524115E+02; // G6
	} else {
		return 7.78344916345091E+01 * x + 2.40558987558802E+01; // G7
	}
}

float colormap_blue(float x) {
	if (x < 0.1418174223507038) {
		return 5.96339971550497E+02 * x + 1.27334281650071E+02; // B1
	} else if (x < 0.2832901246500529) {
		return -5.48535392535404E+02 * x + 2.89697554697557E+02; // B2
	} else if (x < 0.4021748491445084) {
		return 1.22844950213372E+02 * x + 9.95021337126610E+01; // B3
	} else if (x < 0.5699636786725797) {
		return 1.60703217503224E+02 * x + 8.42764907764923E+01; // B4
	} else if (x < 0.7149788470960766) {
		return -3.30626890756314E+02 * x + 3.64316806722696E+02; // B5
	} else if (x < 0.8584529189762473) {
		return -7.30288215340717E+02 * x + 6.50066199802944E+02; // B6
	} else {
		return 5.42814671814679E+02 * x - 4.42832689832695E+02; // B7
	}
}

float4 colormap(float x) {
	float r = clamp(colormap_red(x) / 255.0, 0.0, 1.0);
	float g = clamp(colormap_green(x) / 255.0, 0.0, 1.0);
	float b = clamp(colormap_blue(x) / 255.0, 0.0, 1.0);
	return float4(r, g, b, 1.0);
}

} // namespace CB_Accent
} // namespace IDL
} // namespace colormap
