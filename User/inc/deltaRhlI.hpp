#ifndef deltaRhlI_HPP
#define deltaRhlI_HPP
#include "deltaRhlIStrain.hpp"
#include "Bacter.hpp"

struct deltaRhlI : public Bacter {
public:
	double lasi_signal;
	double rhla, rhlb, rhlc;
	double v_max, v0, v, Pstop;
	
	deltaRhlI(deltaRhlIStrain* strain);

	deltaRhlIStrain* str() {return (deltaRhlIStrain*) strain;};
	
	void setState(Node* rhli_sign_node, Node* lasi_sign_node, Node* haas_node);
	unsigned step(Diffusion& diffusion);
};
#endif
