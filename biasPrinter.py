import ROOT
import sys

masses = [120, 125, 130, 135, 140, 145]
polys = ['pol3', 'pol4']
ROOT.gSystem.Load('lib/libBackgroundProfileFitting.so')
file_list = open("heeBias_all_mssm_fixed/cat3_mu0.0_list.txt")
lines = file_list.readlines()
file_list.close()

bias = []
for m in masses:
    chain = ROOT.TChain("muTree")
    for f in lines:
        if (str(m) in f):
            chain.Add("root://eoscms/"+f.split("\n")[0])

    for poly in polys:
        temp_hist = "temp_hist(100, -5, 5)"
        chain.Draw("pull>>"+ temp_hist+"\"", "genFun==\""+poly+"\" && fitFun==\"mssm\"", "goff")
        temp = ROOT.gDirectory.Get("temp_hist")
        bias.append([m, poly, temp.GetMean()])


a = sorted(bias,key=lambda tup: tup[1])
for b in a:
    print b

#cat0 1.87
#cat1 3.45
#cat2 0.78
#cat3 0.62
