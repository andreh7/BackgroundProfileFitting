#ifndef PdfModelBuilder_h 
#define PdfModelBuilder_h

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "RooRealVar.h"
#include "RooFormulaVar.h"
#include "RooAbsPdf.h"
#include "RooAbsData.h"
#include "RooDataSet.h"
#include "RooProduct.h"
#include "RooWorkspace.h"
#include "TFile.h"

#ifndef __CINT__
#include "MyTimer.h"
#endif

using namespace std;
using namespace RooFit;

class PdfModelBuilder {
  
  public:
    PdfModelBuilder();
    ~PdfModelBuilder();

    void setObsVar(RooRealVar *var);
    void setSignalModifier(RooRealVar *var);
    void setSignalModifierVal(float val);
    void setSignalModifierConstant(bool val);
    void setSignalModifierGaussianConstraint(float val, float sigma);

    void setKeysPdfAttributes(RooDataSet *data, double rho=2);

    void addBkgPdf(string type, int nParams, string name, bool cache=true);

    void setSignalPdf(RooAbsPdf *pdf, RooRealVar *norm=NULL);
    void setSignalPdfFromMC(RooDataSet *data);
    void setSignalPdfFromMC(RooDataHist *data);
    void makeSBPdfs(double bkgYieldInitial, double bkgYieldMin, double bkgYieldMax, bool cache =true);

    map<string,RooAbsPdf*> getBkgPdfs();
    map<string,RooAbsPdf*> getSBPdfs();
    RooAbsPdf *getSigPdf();

    void fitToData(RooAbsData *data, bool bkgOnly=true, bool cache=true, bool print=false, bool resetAfterFit=false, bool runMinosOnMu=false, bool withConstraintOnMu=false);
    void plotPdfsToData(RooAbsData *data, int binning, string name, bool bkgOnly=true, string specificPdfName="", bool getValuesFromCache=false, bool resetAfterPlot=false);
    void plotToysWithPdfs(string prefix, int binning, bool bkgOnly=true);
    void plotHybridToy(string prefix, int binning, vector<float> switchOverMasses, vector<string> functions, bool bkgOnly=true);

    
    void setSeed(int seed);
    void throwToy(string name, int nEvents, bool bkgOnly=true, bool binned=true, bool poisson=true, bool cache=true, bool overrideCachedMu=false, float expectSignal=0.0 );
    RooDataSet *makeHybridDataset(vector<float> switchOverMasses, vector<RooDataSet*> dataForHybrid);
    void throwHybridToy(string name, int nEvents, vector<float> switchOverMasses, vector<string> functions, bool bkgOnly=true, bool binned=true, bool poisson=true, bool cache=true);
    map<string,RooAbsData*> getToyData();
    map<string,RooAbsData*> getHybridToyData();

    void saveWorkspace(TFile* file);
    void saveWorkspace(string filename);

    RooAbsPdf* getBernstein(string prefix, int order);
    RooAbsPdf* getChebychev(string prefix, int order);
    RooAbsPdf* getPowerLaw(string prefix, int order);
    RooAbsPdf* getPowerLawSingle(string prefix, int order);
    RooAbsPdf* getPowerLawGeneric(string prefix, int order);
    RooAbsPdf* getExponential(string prefix, int order);
    RooAbsPdf* getExponentialSingle(string prefix, int order);
    RooAbsPdf* getLaurentSeries(string prefix, int order);
    RooAbsPdf* getHMM(string prefix);
    RooAbsPdf* getMSSM(string prefix);
    RooAbsPdf* getKeysPdf(string prefix);
    RooAbsPdf* getPdfFromFile(string &prefix);

    /** print information about which fit functions needed how much CPU time
	on average */
    void printTimingStatistics(std::ostream &os = std::cout);

    RooWorkspace *wsCache;

  private:
   
    vector<string> recognisedPdfTypes;

    map<string,RooAbsPdf*> bkgPdfs;
    map<string,RooAbsPdf*> sbPdfs;
    RooAbsPdf* sigPdf;
    RooAbsReal* sigNorm;
    RooAbsPdf* sigConstraint;

    RooRealVar *bkgYield;
    RooAbsReal *sigYield;
    RooDataSet *keysPdfData;
    double keysPdfRho;


    map<string,RooAbsData*> toyData;
    map<string,RooAbsData*> toyHybridData;
    map<string,RooDataSet*> toyDataSet;
    map<string,RooDataHist*> toyDataHist;

    map<string,RooRealVar*> params;
    map<string,RooFormulaVar*> prods;
    map<string,RooAbsPdf*> utilities;

    RooRealVar *obs_var;
    bool obs_var_set;
    RooRealVar *signalModifier;
    bool signal_modifier_set;
    bool signal_set;
    bool bkgHasFit;
    bool sbHasFit;
    bool keysPdfAttributesSet;
    vector<string> cut_strings;

    int verbosity;

#ifndef __CINT__
    MyTimer fitTimings;
#endif
};
#endif
