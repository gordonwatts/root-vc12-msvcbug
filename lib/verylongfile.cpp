// Test file to demonstrate a small C++ compiler bug that occurs when nested namespaces are included.
//
// I have done my best to wittle this down to a bare minimum. If I have done my job correctly, then removing
// any line or function argument below will cause the build to succeed.

namespace ROOT {
	namespace Fit {
		class Fitter {
		public:
			template <class Function>
			bool FitFCN(Function fcn);
		};
	}
}

// The function body for FitFCN must be provided seperately. If "{ return false; }" is provided inline
// above, then there is no crash.
template<class Function>
bool ROOT::Fit::Fitter::FitFCN(Function fcn) {
	return false;
}

// This empty decl of a double nested namespace is required. The second "ROOT" causes the failure - if that is commented
// out, then there is a successful compilation.
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
	// The crash happens only if the following two lines are here (even thought they are identical).
	// Further, both arguments must exist in the FitFCN call in order for the compiler crash to happen.
	(long)((ROOT::Fit::Fitter*) 0)->FitFCN(0);
	(long)((ROOT::Fit::Fitter*) 0)->FitFCN(0);
}

