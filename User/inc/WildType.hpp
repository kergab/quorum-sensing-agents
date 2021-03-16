#ifndef WildType_HPP
#define WildType_HPP
#include "WildTypeStrain.hpp"
#include "Bacter.hpp"

struct WildType : public Bacter {
public:
	double rhli_signal, lasi_signal;
	double rhla, rhlb, rhlc;
	double v_max, v0, v, Pstop;
	
	WildType(WildTypeStrain* strain);

	WildTypeStrain* str() {return (WildTypeStrain*) strain;};
	
	void setState(Node* rhli_sign_node, Node* lasi_sign_node, Node* haas_node);
	unsigned step(Diffusion& diffusion);
};
#endif
