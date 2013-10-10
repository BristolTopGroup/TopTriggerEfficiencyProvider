TopTriggerEfficiencyProvider
============================

Providing event weights for lepton+jets top trigger paths

The main method returns a vector with as first element the event weight and the second element the uncertainty on the weight

To run the code, one must specify the lumi of each Dataset you want to compare to the MC
we recommend to process each Dataset (RunA, RunB, RunC and RunD) separately since the trigger menu has changed a lot during the datataking periods.
If you do combine datasets (eg. RunC and RunD), then a weighted average of the efficiency weight is provided

An example on how to run the code can be found in DemoAnalyzer.cc