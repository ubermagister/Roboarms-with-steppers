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
	void printtaaSpeksit(const Speksit& tiedosto) const;
	
	bool lataaSpeksit();



	void tallennaSpeksit(const string& tiedosto) const;

	
	void kyselySpeksit();

private:
	
	std::map<string, Speksit> speksiMap;
	void teecustomSpeksit(const string& nimi);

};

