import os
import sys

inputs = [
    ["", "", "hmmBias_all_mssm_fixed_v2"],
#["Jets01PassPtG10OO_8TeV_125.0","Jets01PassPtG10OO8TeV","passOO"]
]

if (sys.argv[1] == "1"):
    for i in inputs:
        file = open("dat/standardBiasLegacy_hmumu.dat")
        #file = open("dat/standardBiasLegacy_helel.dat")
        lines = file.readlines()
        file.close()

        output = open("dat/standardBiasLegacy_hmumu_"+i[2]+".dat", "w")
        #output = open("dat/standardBiasLegacy_helel_"+i[2]+".dat", "w")
        for l in lines:
            if ("FILENAME" in l):
                output.write(l.replace("FILENAME", i[0]))
            #elif ("workspace" in l):
            #    output.write(l.replace("workspace", i[1]))
            elif ("dirname" in l):
                output.write(l.replace("dirname", i[2]))
            else:
                output.write(l)
        output.close()
        os.system("python scripts/sub_standardBias_jobs.py -D dat/standardBiasLegacy_hmumu_"+i[2]+".dat  -t 1000 -n 10  -q cmscaf1nd --skipPlots")
        #os.system("python scripts/sub_standardBias_jobs.py -D dat/standardBiasLegacy_helel_"+i[2]+".dat  -t 1000 -n 10  -q cmscaf1nd --skipPlots")



if (sys.argv[1] == "2"):
    for i in inputs:
        os.system("scripts/prepareStdBiasToysTreeLists.csh /eos/cms/store/caf/user/sani/BiasStudy/"+i[2]+"/ "+i[2])



if (sys.argv[1] == "3"):
    #output = open("dat/bsConfig_2012_hmm_hists.dat", "w")
    output = open("dat/bsConfig_2012_hee_hists.dat", "w")
    for n,i in enumerate(inputs):
        for j in xrange(4):
            output.write("cat=("+str(j)+",0.0)\n")
            output.write("plot=mu(1000:-10000:-10000),err_mu(250:0:250),pull_mu(400:-5.0:5.0)\n")
            output.write("input="+i[2]+"/cat"+str(j)+"_mu0.0_list.txt\n")
            output.write("outfile=root://eoscms//eos/cms/store/caf/user/sani/BiasStudy/"+i[2]+"/biasStudy_"+i[2]+"_cat"+str(j)+"_mu0.0_list.root\n")
            output.write("#######  cat "+str(j)+" with muInj 0.0 ######\n")
    output.close()
    #os.system("python scripts/make_hists_simplebias_from_tree_hmm.py -d dat/bsConfig_2012_hmm_hists.dat")
    os.system("python scripts/make_hists_simplebias_from_tree_hmm.py -d dat/bsConfig_2012_hee_hists.dat")




if (sys.argv[1] == "4"):
    for i in inputs:
        for j in xrange(4):
            os.system("python scripts/draw_simplebias_plots.py -i root://eoscms//eos/cms/store/caf/user/sani/BiasStudy/"+i[2]+"/biasStudy_"+i[2]+"_cat"+str(j)+"_mu0.0_list.root -o "+i[2])
