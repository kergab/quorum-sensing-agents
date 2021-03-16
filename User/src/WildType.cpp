#include "WildType.hpp"
#include "Diffusion.hpp"

enum StateFlags{rhli_state = 1, lasi_state = 2, sadc_signal = 4, };

WildType::WildType(WildTypeStrain* str) : Bacter(str) {}

void WildType::setState(Node* rhli_sign_node, Node* lasi_sign_node, Node* haas_node) {
	bool rhli = false, lasi = false, sadc = false;

	double rhli_sign_c = rhli_sign_node->value;
	double lasi_sign_c = lasi_sign_node->value;
	
	if(rhli_sign_c > str()->rhli_sign_treshold) {
		rhli = true;

		if(lasi_sign_c > str()->lasi_sign_treshold) {
			lasi = true;
			
			bite = str()->bite_3;
			loss = str()->loss_3;
			rhli_signal = str()->rhli_sign_max;
			lasi_signal = str()->lasi_sign_max;
			rhla = str()->rhla_max;
			rhlb = str()->rhlb_max;
			rhlc = str()->rhlc_max;
			v_max = str()->v_max_2;
		}
		else {
			bite = str()->bite_2;
			loss = str()->loss_2;
			rhli_signal = str()->rhli_sign_inter;
			lasi_signal = str()->lasi_sign_inter;
			rhla = str()->rhla_min;
			rhlb = str()->rhlb_min;
			rhlc = str()->rhlc_min;
			v_max = str()->v_max_1;
		}
	}
	else {
		if(lasi_sign_c > str()->lasi_sign_treshold) {
			lasi = true;
			
			bite = str()->bite_1;
			loss = str()->loss_1;
			rhli_signal = str()->rhli_sign_max;
			lasi_signal = str()->lasi_sign_max;
			rhla = str()->rhla_base;
			rhlb = str()->rhlb_base;
			rhlc = str()->rhlc_base;
			v_max = str()->v_max_0;
		}
		else {
			bite = str()->bite_0;
			loss = str()->loss_0;
			rhli_signal = str()->rhli_sign_base;
			lasi_signal = str()->lasi_sign_base;
			rhla = str()->rhla_base;
			rhlb = str()->rhlb_base;
			rhlc = str()->rhlc_base;
			v_max = str()->v_max_0;
		}
	}
	if(haas_node->value > str()->haa_treshold) {
		sadc = true;

		if(rhli) {
			bite = str()->bite_5;
			loss = str()->loss_5;
			v_max = str()->v_max_12_1;
		}
		else {
			bite = str()->bite_4;
			loss = str()->loss_4;
			v_max = str()->v_max_0_1;
		}
	}
	stateFlags = (rhli? rhli_state : 0) | (lasi? lasi_state : 0) | (sadc? sadc_signal : 0);
	if(sadc) color = 2;
	else color = (rhli && lasi)? 1 : 0;
}

unsigned WildType::step(Diffusion& diffusion) {
	Node* food_node = diffusion.node(toPoint(), food);
	Node* rhli_sign_node = diffusion.node(toPoint(), rhli_sign);
	Node* lasi_sign_node = diffusion.node(toPoint(), lasi_sign);
	Node* haas_node = diffusion.node(toPoint(), haas);
	Node* mono_rls_node = diffusion.node(toPoint(), mono_rls);
	Node* di_rls_node = diffusion.node(toPoint(), di_rls);
	
	setState(rhli_sign_node, lasi_sign_node, haas_node);
	
	if(mass > loss) {
		rhli_sign_node->value += rhli_signal;
		lasi_sign_node->value += lasi_signal;
		haas_node->value += rhla;
		mono_rls_node->value += rhlb;
		di_rls_node->value += rhlc;
	}
	if(mass < str()->critical_mass) return Dead;
	
	double RHLC = (di_rls_node->value)/(di_rls_node->value + str()->rhlc_half_effect);
	double RHLB = (mono_rls_node->value)/(mono_rls_node->value + str()->rhlb_half_effect);
	double RHLA = (haas_node->value)/(haas_node->value + str()->rhla_half_effect);
	double RHLABC = (RHLC + RHLB + RHLA > 1)? 1 : (RHLC + RHLB + RHLA);
	
	v0 = v_max / str()->v_fraction;
	v = v0 + (v_max - v0)*RHLABC;
	QPointF gradSpeed = di_rls_node->grad() * RHLC * v * 8.0;
	gradSpeed -= haas_node->grad() * RHLA * v * 1.0;
	if(Position::step(diffusion.size(), v, gradSpeed) != Position::In) return Dead;
	
	Pstop = (v_max <= str()->v_treshold) ? ((str()->v_treshold - v_max)/str()->v_treshold) : 0;
	
	double f = (food_node->value < bite)? food_node->value : bite;
	mass += f;
	if(!(food_node->flag & Fixed)) food_node->value -= f;
	
	if(mass > (str()->division)) return Divide;
	return Normal;
}





