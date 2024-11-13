#pragma once

class kiihdyttaja
{
public:
	struct Speksit {
		string nimi;
		double GearRatio;
		double StepAngle;
		double jaksonkulma;
		double jaksonaika;
	

	};
	void printtaaSpeksit(const Speksit& speksi) const{};
	
	bool lataaSpeksit(const std::string& filename);


	void tallennaSpeksit(const std::string& filename) const;

	
	void kyselySpeksit();

private:
	
	std::map<string, Speksit> speksiMap;
	void teecustomSpeksit(const string& name);

};

