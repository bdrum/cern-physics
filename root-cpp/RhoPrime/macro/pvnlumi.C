Int_t nRuns = 59;
Int_t runList[] = {
  295788, 295819, 295822, 295826, 295908, 295910, 295913, 296063, 296134, 296191,
  296194, 296244, 296269, 296273, 296304, 296377, 296378, 296414, 296415, 296433,
  296509, 296510, 296549, 296550, 296618, 296690, 296694, 296749, 296750, 296784,
  296787, 296794, 296836, 296839, 296849, 296850, 296890, 296894, 296900, 296930,
  296934, 296935, 296938, 296941, 296966, 297029, 297031, 297119, 297123, 297128,
  297129, 297193, 297194, 297218, 297219, 297317, 297367, 297372, 297379
};

void pvnlumi(){
  gStyle->SetOptStat(0);
  gStyle->SetLineScalePS(1.5);

  t = new TChain("trending");
  t->AddFile("trending_merged_PbPb.root");
  TObjArray* classes = new TObjArray();
  Double_t  class_lumi[300] = {0};
  ULong64_t class_lMb[300] = {0};
  ULong64_t class_l0b[300] = {0};
  ULong64_t class_l0a[300] = {0};
  ULong64_t class_l1b[300] = {0};
  ULong64_t class_l1a[300] = {0};
  Double_t  class_lifetime[300];
  Double_t  class_ds[300];
  Double_t interactionRate = 0;
  Double_t run_duration = 0;
  Int_t run;
  Int_t fill;
  Int_t bcs;
  Double_t mu = 0;
  Double_t lumi_seen;
  t->SetBranchAddress("mu",&mu);
  t->SetBranchAddress("run",&run);
  t->SetBranchAddress("fill",&fill);
  t->SetBranchAddress("bcs",&bcs);
  t->SetBranchAddress("classes",&classes);
  t->SetBranchAddress("class_lumi",&class_lumi);
  t->SetBranchAddress("class_lMb",&class_lMb);
  t->SetBranchAddress("class_l0b",&class_l0b);
  t->SetBranchAddress("class_l0a",&class_l0a);
  t->SetBranchAddress("class_l1b",&class_l1b);
  t->SetBranchAddress("class_l1a",&class_l1a);
  t->SetBranchAddress("class_ds",&class_ds);
  t->SetBranchAddress("class_lifetime",&class_lifetime);
  t->SetBranchAddress("interactionRate",&interactionRate);
  t->SetBranchAddress("lumi_seen", &lumi_seen);
  t->SetBranchAddress("run_duration", &run_duration);
  t->BuildIndex("run");
  Double_t lumi = 0;

  TH1D* hLumi = new TH1D("hLumi","",nRuns,0,nRuns);
  TH1D* hInteractionRate = new TH1D("hInteractionRate","",nRuns,0,nRuns);
  TH1D* hMu = new TH1D("hMu","#mu(INEL)",nRuns,0,nRuns);

  int prev = 0;
  for (Int_t i=0;i<nRuns;i++){
    Int_t r = runList[i];
  //  for (Int_t i=295580;i<295754;i++){
  //    Int_t r = i;

    char* srun = Form("%i",r);
    t->GetEntryWithIndex(r);

    TString className="CCUP31-U-NOPF-CENTNOTRD";
    AliTriggerClass* cl = (AliTriggerClass*) classes->FindObject(className.Data());

    if( !cl ) continue;

    Int_t iclass = classes->IndexOf(cl);

    if( class_l0a[iclass] < 0000 || class_l0a[iclass] == prev ) continue;
    prev = class_l0a[iclass];

    //    std::cout<<runList[i]<<" "<<class_lumi[iclass]<<std::endl;
    std::cout<<i<<" "<<iclass<<" "<<class_lumi[iclass]<<" "<<class_l0a[iclass]<<" "<<class_l1a[iclass]<<std::endl;

    hLumi->Fill(srun,class_lumi[iclass]);

    hInteractionRate->Fill(srun,interactionRate);
    hMu->Fill(srun,mu);
    lumi+=class_lumi[iclass];
    double val = class_l0b[iclass];
    double vallum = lumi_seen;
  }
  printf("Total lumi = %f\n",lumi);

  hMu->LabelsDeflate("x");
  for (Int_t i=1;i<=hMu->GetNbinsX();i++){
    Int_t l = TString(hMu->GetXaxis()->GetBinLabel(i)).Atoi();
    printf("%i, ",l);
    if (i%10==0) printf("\n");
  }
  printf("\n");
  //  TFile* f = new TFile("lumi_cmup11.root","recreate");
  TFile* f = new TFile("tmp.root","recreate");
  hLumi->Write();
  hInteractionRate->Write();
  hMu->Write();
  f->Close();
}
