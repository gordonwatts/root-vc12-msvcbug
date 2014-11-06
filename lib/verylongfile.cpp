// Since CINT ignores the std namespace, we need to do so in this file.
using namespace std;
#include "G__MathFit.h"

//void G__letint(int junk, int type, long value);

namespace ROOT {
	namespace Fit {
		// THis double nested same name is what causes the compiler error
#ifndef compileok
		namespace ROOT {
		}
#endif
	}
}

// If either of these lines in the code below are removed, the crash will happen.
void badcode(struct G__param* libp)
{
	// This line needs to be here to cause the crash
	G__letint(0,
		0,
		(long)((ROOT::Fit::Fitter*) G__getstructoffset())->FitFCN(*(ROOT::Math::IMultiGenFunction*) libp->para[0].ref, (double*)G__int(libp->para[1]), (unsigned int)G__int(libp->para[2]))
		);

	// The crash seems to happen on this line.
	G__letint(0,
		0,
		(long)((ROOT::Fit::Fitter*) G__getstructoffset())->FitFCN(*(ROOT::Math::IMultiGenFunction*) libp->para[0].ref, (double*)G__int(libp->para[1]))
		);
}

