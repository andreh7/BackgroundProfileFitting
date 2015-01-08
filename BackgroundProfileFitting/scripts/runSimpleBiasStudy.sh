#!/bin/tcsh

# ----- launch toys ------- --skipPlots
scripts/sub_standardBias_jobs.py -D dat/standardBiasLegacy_massFac.dat -t 1000 -n 10  -q cmscaf1nd --skipPlots
# ----- make list of trees per job type  -------
scripts/prepareStdBiasToysTreeLists.csh /eos/cms/store/caf/user/sani/BiasStudy/test/ test_trees
# ----- prepare histograms of pulls from trees -------
scripts/make_hists_simplebias_from_tree.py -d dat/bsConfig_2012_legacy_freeze_v2_massFac_hists.dat
# ----- to make final plots ------  
scripts/draw_simplebias_plots.py -i root://eoscms//eos/cms/store/caf/user/sani/BiasStudy/legacy_freeze_v2_massFac_e/biasStudy_legacy_freeze_v2_massFac_e_cat0_mu1.0_list.root -o test_plots


scripts/sub_standardBias_jobs.py -D dat/standardBiasLegacy_hmumu.dat -t 1000 -n 10  -q cmscaf1nd --skipPlots
