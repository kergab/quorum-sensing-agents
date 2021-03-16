#ifndef Generate_HPP
#define Generate_HPP
#include "Params.hpp"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <iostream>

class Generate {
protected:
	QString prefix;
public:
	Generate(QString prf = "generated/") : prefix(prf) {}

	bool bacterStrainHpp(StrainDescriptor& strainDescriptor) {
		QFile file(prefix + "inc/" + strainDescriptor.name + "Strain.hpp");
		if(!file.open(QFile::WriteOnly | QFile::Truncate)) return false;
		QTextStream s(&file);
		s << "#ifndef " << strainDescriptor.name << "Strain_HPP\n";
		s << "#define " << strainDescriptor.name << "Strain_HPP\n";
		s << "#include \"Strain.hpp\"\n";
		s << "#include \"Params.hpp\"\n\n";
		s << "class " << strainDescriptor.name << "Strain : public Strain {\npublic:\n";
		for(Param& param : strainDescriptor.variables) {s << "\t" << param.type << " " << param.name << ";\n";}
		for(StateParams& state : strainDescriptor.states) {
			s << "\n\t//state " << state.id << "\n";
			for(Param& param : state) {s << "\t" << param.type << " " << param.name << ";\n";}
		}
		s << "\n\tvoid init(StrainDescriptor& strainDescriptor) {\n";
		s << "\t\tdivision = strainDescriptor.division" << ";\n";
		for(unsigned n = 0; n < strainDescriptor.variables.size(); n++) {
			s << "\t\t" << strainDescriptor.variables[n].name << " = ";
			s << "strainDescriptor.variables[" << n << "].value";
			if(strainDescriptor.variables[n].type == "double") s << ".toDouble()";
			else if(strainDescriptor.variables[n].type == "int") s << ".toInt()";
			s << ";\n";
		}
		for(unsigned n = 0; n < strainDescriptor.states.size(); n++) {
			s << "\t\t\n";
			for(unsigned m = 0; m < strainDescriptor.states[n].size(); m++) {
				s << "\t\t" << strainDescriptor.states[n][m].name << " = ";
				s << "strainDescriptor.states[" << n << "][" << m << "].value";
				if(strainDescriptor.states[n][m].type == "double") s << ".toDouble()";
				else if(strainDescriptor.variables[n].type == "int") s << ".toInt()";
				s << ";\n";
			}
		}
		s << "\t};\n";
		s << "\tBacter* bacter();\n";
		s << "};\n";
		s << "#endif\n";
		return true;
	}
	bool bacterHpp(StrainDescriptor& strainDescriptor) {
		QFile file(prefix + "inc/" + strainDescriptor.name + ".hpp");
		if(!file.open(QFile::WriteOnly | QFile::Truncate)) return false;
		QTextStream s(&file);
		s << "#ifndef " << strainDescriptor.name << "_HPP\n";
		s << "#define " << strainDescriptor.name << "_HPP\n";
		s << "#include \"" << strainDescriptor.name + "Strain.hpp\"\n";
		s << "#include \"Bacter.hpp\"\n\n";
		s << "struct " << strainDescriptor.name << " : public Bacter {\npublic:\n";
		s << "\t" << strainDescriptor.name << "(" << strainDescriptor.name << "Strain* strain);\n\n";
		s << "\t" << strainDescriptor.name << "Strain* str() {return (" << strainDescriptor.name << "Strain*) strain;};\n\n";
		s << "};\n";
		s << "#endif\n";
		return true;
	}
	bool bacterStrainCpp(StrainDescriptor& strainDescriptor) {
		QFile file(prefix + "src/" + strainDescriptor.name + "Strain.cpp");
		if(!file.open(QFile::WriteOnly | QFile::Truncate)) return false;
		QTextStream s(&file);
		s << "#include \"" << strainDescriptor.name << "Strain.hpp\"\n";
		s << "#include \"" << strainDescriptor.name << ".hpp\"\n\n";
		s << "Bacter* " << strainDescriptor.name << "Strain::bacter() {return new ";
		s << strainDescriptor.name << "(this);}\n\n";
		return true;
	}
	bool bacterCpp(StrainDescriptor& strainDescriptor) {
		QFile file(prefix + "src/" + strainDescriptor.name + ".cpp");
		if(!file.open(QFile::WriteOnly | QFile::Truncate)) return false;
		QTextStream s(&file);
		s << "#include \"" << strainDescriptor.name << ".hpp\"\n\n";
		s << "enum StateFlags{";
		for(QString& signal : strainDescriptor.stateSignals) s << signal << ", ";
		s << "};\n\n";
		s << strainDescriptor.name << "::" << strainDescriptor.name;
		s << "(" << strainDescriptor.name << "Strain* str) : Bacter(str) {";
		s << "}\n";
		return true;
	}
	bool pri(Params& params) {
		QFile file(prefix + "generated.pri");

		QDir dir;
		if (!dir.exists(prefix)) {
		    dir.mkpath(prefix);
		}

		if(!file.open(QFile::WriteOnly | QFile::Truncate)) return false;
		QTextStream s(&file);
		for(StrainDescriptor& strainDescriptor : params.strainDescriptors) {
			s << "HEADERS\t\t+= ../User/inc/" << strainDescriptor.name << ".hpp\n";
			s << "HEADERS\t\t+= ../User/inc/" << strainDescriptor.name << "Strain.hpp\n";
			s << "HEADERS\t\t+= ../User/inc/SubstanceNames.hpp\n";
			s << "SOURCES\t\t+= ../User/src/" << strainDescriptor.name << ".cpp\n";
			s << "SOURCES\t\t+= ../User/src/" << strainDescriptor.name << "Strain.cpp\n";
		}
		s << "SOURCES\t\t+= ../User/src/Strains.cpp\n";
		return true;
	}
	bool substanceNamesHpp(SubstanceDescriptors& substanceDescriptors) {
		QFile file(prefix + "inc/SubstanceNames.hpp");

		QDir dir;
		if (!dir.exists(prefix + "inc/")) {
		    dir.mkpath(prefix + "inc/");
		}

		if(!file.open(QFile::WriteOnly | QFile::Truncate)) return false;
		QTextStream s(&file);
		s << "enum SubstanceName{";
		for(SubstanceDescriptor& sd : substanceDescriptors) s << sd.name << ", ";
		s << "};\n";
		return true;
	}
	bool files(Params& params) {
		bool ok = pri(params) && substanceNamesHpp(params.substanceDescriptors);
		QFile file(prefix + "src/Strains.cpp");

		QDir dir;
		if (!dir.exists(prefix + "src/")) {
		    dir.mkpath(prefix + "src/");
		}


		if(!file.open(QFile::WriteOnly | QFile::Truncate)) return false;
		QTextStream s(&file);
		s << "#include \"Strains.hpp\"\n";
		s << "#include \"Params.hpp\"\n";
		s << "#include \"Strain.hpp\"\n";
		s << "#include \"Diffusion.hpp\"\n";
		for(StrainDescriptor& strainDescriptor : params.strainDescriptors) {
			s << "#include \"" << strainDescriptor.name << "Strain.hpp\"\n";
		}
		s << "\n";
		s << "Strains::Strains(Params& params) {\n";
		for(StrainDescriptor& strainDescriptor : params.strainDescriptors) {
			ok &= bacterStrainHpp(strainDescriptor);
			ok &= bacterHpp(strainDescriptor);
			ok &= bacterStrainCpp(strainDescriptor);
			ok &= bacterCpp(strainDescriptor);
			s << "\tpush_back(new " << strainDescriptor.name << "Strain);\n";
		}
		s << "\tif(!(ok = params.ok)) return;\n";
		s << "\tfor(unsigned n = 0; n < size(); n++) {\n";
		s << "\t\tat(n)->init(params.strainDescriptors[n]);\n";
		s << "\t\tat(n)->set(params.strainDescriptors[n]);\n";
		s << "\t}\n";
		s << "}\n\n";
		s << "Strains::~Strains() {for(Strain* strain : *this) delete strain;}\n";
		s << "void Strains::step(Diffusion& diffusion) {for(Strain* strain : *this) strain->step(diffusion);}\n";
		return ok;
	}
};
#endif
