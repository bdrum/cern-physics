
int nRuns = 124;
int runList[] = {245145, 245146, 245151, 245152, 245231, 245232, 245259, 245345,
       245346, 245347, 245349, 245353, 245396, 245397, 245401, 245407,
       245409, 245410, 245411, 245441, 245446, 245450, 245453, 245454,
       245496, 245497, 245501, 245504, 245505, 245507, 245540, 245542,
       245543, 245544, 245545, 245554, 245683, 245692, 245700, 245702,
       245705, 245775, 245793, 245829, 245831, 245833, 245923, 245949,
       245952, 245954, 245963, 246001, 246003, 246012, 246036, 246037,
       246042, 246048, 246049, 246052, 246053, 246087, 246089, 246113,
       246115, 246148, 246151, 246152, 246153, 246178, 246180, 246181,
       246182, 246185, 246217, 246222, 246225, 246271, 246272, 246275,
       246276, 246424, 246428, 246431, 246434, 246487, 246488, 246493,
       246495, 246675, 246676, 246750, 246751, 246757, 246758, 246759,
       246760, 246763, 246765, 246766, 246804, 246805, 246807, 246808,
       246809, 246810, 246844, 246845, 246846, 246847, 246851, 246864,
       246865, 246867, 246871, 246928, 246945, 246948, 246980, 246982,
       246984, 246989, 246991, 246994};

void lumi(){

  std::map<int,float> runLumi;
  auto t = new TChain("trending");
  t->AddFile("/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/RhoPrime/2015/trending_merged_PbPb.root");
  TObjArray* classes = new TObjArray();
  Double_t  class_lumi[300] = {0};
  ULong64_t class_l0a[300] = {0};
  Int_t run;
  t->SetBranchAddress("run",&run);
  t->SetBranchAddress("classes",&classes);
  t->SetBranchAddress("class_lumi",&class_lumi);
  t->SetBranchAddress("class_l0a",&class_l0a);
  t->BuildIndex("run");
  Double_t lumi = 0;


  int prev = 0;
  for (Int_t i=0;i<nRuns;i++){
    Int_t r = runList[i];
    t->GetEntryWithIndex(r);

    TString className="CCUP9-B-NOPF-CENTNOTRD";
    AliTriggerClass* cl = (AliTriggerClass*) classes->FindObject(className.Data());

    if( !cl ) continue;

    Int_t iclass = classes->IndexOf(cl);

    if( class_l0a[iclass] < 0 || class_l0a[iclass] == prev ) continue;
    prev = class_l0a[iclass];

    //std::cout<<runList[i]<<" "<<class_lumi[iclass]<<std::endl;
    runLumi[runList[i]]=class_lumi[iclass];


    //std::cout<<i<<" "<<iclass<<" "<<class_lumi[iclass]<<" "<<class_l0a[iclass]<<" "<<class_l1a[iclass]<<std::endl;

    lumi+=class_lumi[iclass];
  }
  printf("Total lumi = %f\n",lumi);

  for (auto const& x : runLumi)
  {
      std::cout << x.first  << ':' << x.second << "," ;
}

}
