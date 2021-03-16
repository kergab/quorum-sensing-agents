#ifndef deltaRhlIStrain_HPP
#define deltaRhlIStrain_HPP
#include "Strain.hpp"
#include "Params.hpp"

class deltaRhlIStrain : public Strain {
public:
	double rhli_sign_treshold;
	double lasi_sign_treshold;
	double haa_treshold;
	double rhla_half_effect;
	double rhlb_half_effect;
	double rhlc_half_effect;
	double v_fraction;

	//state q0
	double bite_0;
	double loss_0;
	double lasi_sign_base;
	double rhla_base;
	double rhlb_base;
	double rhlc_base;
	double v_max_0;

	//state q1
	double bite_1;
	double loss_1;
	double lasi_sign_max;

	//state q2
	double bite_2;
	double loss_2;
	double lasi_sign_inter;
	double rhla_min;
	double rhlb_min;
	double rhlc_min;
	double v_max_1;

	//state q3
	double bite_3;
	double loss_3;
	double rhla_max;
	double rhlb_max;
	double rhlc_max;
	double v_max_2;

	//state sadc1
	double bite_4;
	double loss_4;
	double v_max_0_1;

	//state sadc2
	double bite_5;
	double loss_5;
	double v_max_12_1;

	void init(StrainDescriptor& strainDescriptor) {
		division = strainDescriptor.division;
		rhli_sign_treshold = strainDescriptor.variables[0].value.toDouble();
		lasi_sign_treshold = strainDescriptor.variables[1].value.toDouble();
		haa_treshold = strainDescriptor.variables[2].value.toDouble();
		rhla_half_effect = strainDescriptor.variables[3].value.toDouble();
		rhlb_half_effect = strainDescriptor.variables[4].value.toDouble();
		rhlc_half_effect = strainDescriptor.variables[5].value.toDouble();
		v_fraction = strainDescriptor.variables[6].value.toDouble();
		
		bite_0 = strainDescriptor.states[0][0].value.toDouble();
		loss_0 = strainDescriptor.states[0][1].value.toDouble();
		lasi_sign_base = strainDescriptor.states[0][2].value.toDouble();
		rhla_base = strainDescriptor.states[0][3].value.toDouble();
		rhlb_base = strainDescriptor.states[0][4].value.toDouble();
		rhlc_base = strainDescriptor.states[0][5].value.toDouble();
		v_max_0 = strainDescriptor.states[0][6].value.toDouble();
		
		bite_1 = strainDescriptor.states[1][0].value.toDouble();
		loss_1 = strainDescriptor.states[1][1].value.toDouble();
		lasi_sign_max = strainDescriptor.states[1][2].value.toDouble();
		
		bite_2 = strainDescriptor.states[2][0].value.toDouble();
		loss_2 = strainDescriptor.states[2][1].value.toDouble();
		lasi_sign_inter = strainDescriptor.states[2][2].value.toDouble();
		rhla_min = strainDescriptor.states[2][3].value.toDouble();
		rhlb_min = strainDescriptor.states[2][4].value.toDouble();
		rhlc_min = strainDescriptor.states[2][5].value.toDouble();
		v_max_1 = strainDescriptor.states[2][6].value.toDouble();
		
		bite_3 = strainDescriptor.states[3][0].value.toDouble();
		loss_3 = strainDescriptor.states[3][1].value.toDouble();
		rhla_max = strainDescriptor.states[3][2].value.toDouble();
		rhlb_max = strainDescriptor.states[3][3].value.toDouble();
		rhlc_max = strainDescriptor.states[3][4].value.toDouble();
		v_max_2 = strainDescriptor.states[3][5].value.toDouble();
		
		bite_4 = strainDescriptor.states[4][0].value.toDouble();
		loss_4 = strainDescriptor.states[4][1].value.toDouble();
		v_max_0_1 = strainDescriptor.states[4][2].value.toDouble();
		
		bite_5 = strainDescriptor.states[5][0].value.toDouble();
		loss_5 = strainDescriptor.states[5][1].value.toDouble();
		v_max_12_1 = strainDescriptor.states[5][2].value.toDouble();
	};
	Bacter* bacter();
};
#endif
