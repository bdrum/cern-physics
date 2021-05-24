#include "TH1.h"
#include "TF1.h"
#include "TMath.h"
#include <cmath>
#include <complex>

Double_t par[9], pars[9], parsn[9];
TH1F *upair, *lpair;

gStyle->SetOptStat(0);
gStyle->SetOptTitle(0);
int kr = 2;

int npar = 7;
bool simplyrho = true;

void bw() {

  TFile *fres = new TFile("selout.hist.root");

  upair = (TH1F*)fres->Get("hUnlikePairMassH");
  upair->Rebin(kr);
  upair->Sumw2();
  upair->SetLineWidth(3);
  lpair = (TH1F*)fres->Get("hLikePairMassH")->Clone("ugu");
  lpairdraw = (TH1F*)fres->Get("hLikePairMassH")->Clone("ugun");
  lpairdraw->Rebin(kr);
  lpair->Rebin(kr);
  TF1 *frho1 = new TF1("frho1",frho,0.3,2.5,npar);
  TF1 *frho2 = new TF1("frho2",frho,0.3,2.5,npar);
  TF1 *frho3 = new TF1("frho3",frho,0.3,2.5,npar);
  frho1->SetParameter(0,1.5); frho1->SetParameter(1,0.2); frho1->SetParameter(2,50.);
  frho1->SetParameter(4,1.5); frho1->SetParameter(5,0.2); frho1->SetParameter(6,50.);
  frho1->SetParameter(3,1.);
  frho1->SetLineWidth(3);
  upair->SetAxisRange(0.3,1.5,"X");

  upair->Fit("frho1","R");

  frho1->GetParameters(par);
  frho1->GetParameters(pars);
  par[3]=0.;
  frho2->SetParameters(par);
  frho2->SetLineWidth(3);
  frho2->SetLineColor(3);
  frho2->Draw("same,hist");
  pars[2]=0.;
  frho3->SetParameters(pars);
  frho3->SetLineWidth(3);
  frho3->SetLineColor(4);
  frho3->Draw("same,hist");
  //  break;






  res = (TH1F*)fres->Get("hTotMass1");
  lpair = (TH1F*)fres->Get("hTotMassnon1");
  res->Rebin(2);
  res->Sumw2();
  lpair->Rebin(2);
  lpair->Sumw2();
  //  resn->Add(resn,resn,375./625.,0.);
  //  res->Draw("e");
  //  lpair->Draw("same,hist");
  //  break;

  float rl = 1., rh = 2.5;
  res->SetAxisRange(rl,rh,"X");

  frho1->SetParameter(0,1.5); frho1->SetParameter(1,0.2); frho1->SetParameter(2,50.);
  frho1->SetParameter(4,1.5); frho1->SetParameter(5,0.2); frho1->SetParameter(6,50.);
  frho1->SetParameter(3,10.); frho1->SetParLimits(3,0.,1.);
  frho1->SetLineWidth(3);
  frho1->SetParName(0,"mass");
  frho1->SetParName(1,"width");
  frho1->SetParName(2,"normalization");

  simplyrho = false;
  res->Fit("frho1","R");

  frho1->GetParameters(par);   frho1->GetParameters(pars);   frho1->GetParameters(parsn);
  par[3]=0.; par[6]=0.;
  frho2->SetParameters(par);
  frho2->SetLineWidth(3);
  frho2->SetLineColor(3);
  frho2->Draw("same,hist");
  pars[2]=0.;
  frho3->SetParameters(pars);
  frho3->SetLineWidth(3);
  frho3->SetLineColor(4);
  frho3->Draw("same,hist");
  break;

  bw->SetLineColor(2);
  bw->SetParameters(par);
  bw->SetParameter(3,10.);
  bw->Draw("same,hist");

}

Double_t frho(Double_t *x, Double_t *par ) {
  Double_t xx = x[0], fff;
  Double_t pmass = 0.13957, rhom, wrho, q, q0rho, ratrho1, gtot;

  rhom = par[0]; wrho = par[1];
  q = sqrt( xx**2/4. - pmass**2);
  q0rho=sqrt(rhom**2/4.-pmass**2 );
  ratrho1 = std::pow(q/q0rho,3)/((q/q0rho)**2+1.)*2.;
  gtot = wrho*ratrho1;
  fff = par[2] * gtot * xx * rhom / ( (xx**2 - rhom**2)**2 + rhom**2*gtot**2);

  if( npar == 7 && !simplyrho ) {
    rhom = par[4]; wrho = par[5];
    q = sqrt( xx**2/4. - pmass**2);
    q0rho=sqrt(rhom**2/4.-pmass**2 );
    ratrho1 = std::pow(q/q0rho,3)/((q/q0rho)**2+1.)*2.;
    gtot = wrho*ratrho1;
    fff = fff + par[6] * gtot * xx * rhom / ( (xx**2 - rhom**2)**2 + rhom**2*gtot**2);
  }
  
  Int_t bin = (lpair->GetXaxis())->FindBin(xx);
  Double_t like = par[3]*(lpair->GetBinContent(bin));
  
  return fff+like;
}

Double_t fnonrel(Double_t *x, Double_t *par ) {
   Double_t xx = x[0];
   Double_t pmass=0.140, rhom = par[0], wrho = par[1];
   Double_t fff = par[2] * wrho/((xx-rhom)**2+(wrho/2.)**2)/2./sqrt(3.14);
   Int_t bin = (lpair->GetXaxis())->FindBin(xx);
   Double_t like = par[3]*(lpair->GetBinContent(bin));

   return fff;
}

Double_t frelback(Double_t *x, Double_t *par ) {
   Double_t xx = x[0];

   Double_t pmass=0.13957, rhom = par[0], wrho = par[1];
   Double_t q = sqrt( xx**2/4. - pmass**2);
   Double_t q0rho=sqrt(rhom**2/4.-pmass**2 );
   Double_t ratrho1 = std::pow(q/q0rho,3)/((q/q0rho)**2+1.)*2.;
   Double_t gtot = wrho*ratrho1;
   Double_t fff = par[2] * gtot * xx * rhom / ( (xx**2 - rhom**2)**2 + rhom**2*gtot**2);
     
   Int_t bin = (lpair->GetXaxis())->FindBin(xx);
   Double_t like = par[3]*(lpair->GetBinContent(bin));

   return fff + like;
}

Double_t frelsod(Double_t *x, Double_t *par ) {
   Double_t xx = x[0];

   double rhomass=par[0];
   double rhomass2=rhomass*rhomass;
   double rhowidth=par[1];
   double pionmass=0.13957;
   double pionmass2=pionmass*pionmass;

   // rho mass-dependent width                                                                                                                                          
   double val=std::pow((xx*xx-4*pionmass2)/(rhomass2-4*pionmass2),1.5);
   double mdwidth=rhowidth*(rhomass/xx)*val; // mass dependent width                                                                                                    

   std::complex<double> ix=std::complex<double>(0,1);
   std::complex<double> denom=xx*xx-rhomass2+ix*rhomass*mdwidth;
   std::complex<double> aterm=par[2]*std::sqrt(xx*rhomass*mdwidth)/denom;
   std::complex<double> bterm=par[3];
   std::complex<double> total=(aterm+bterm)*(aterm+bterm);
   double fff=std::abs(total);
     
   Int_t bin = (lpair->GetXaxis())->FindBin(xx);
   Double_t like = par[3]*(lpair->GetBinContent(bin));

   return fff + like;
}

Double_t ffff(Double_t *x, Double_t *par ) {
   Double_t xx = x[0];

   double rhomass=par[0];
   double rhomass2=rhomass*rhomass;
   double rhowidth=par[1];
   double pionmass=0.13957;
   double pionmass2=pionmass*pionmass;
  
   // rho mass-dependent width
   double val=std::pow((xx*xx-4*pionmass2)/(rhomass2-4*pionmass2),1.5);
   double mdwidth=rhowidth*(rhomass/xx)*val; // mass dependent width
  
   std::complex<double> ix=std::complex<double>(0,1);
   std::complex<double> denom=xx*xx-rhomass2+ix*rhomass*mdwidth;
   std::complex<double> aterm=par[2]*std::sqrt(xx*rhomass*mdwidth)/denom;
   std::complex<double> total=aterm*aterm;
   double amp=std::abs(total);

   return amp;
}

Double_t finter(Double_t *x, Double_t *par ) {
   Double_t xx = x[0];

   double rhomass=par[0];
   double rhomass2=rhomass*rhomass;
   double rhowidth=par[1];
   double pionmass=0.13957;
   double pionmass2=pionmass*pionmass;

   // rho mass-dependent width                                                                                                                                          
   double val=std::pow((xx*xx-4*pionmass2)/(rhomass2-4*pionmass2),1.5);
   double mdwidth=rhowidth*(rhomass/xx)*val; // mass dependent width                                                                                                    

   std::complex<double> ix=std::complex<double>(0,1);
   std::complex<double> denom=std::complex<double>(xx*xx-rhomass2,rhomass*mdwidth);
   std::complex<double> aterm=par[2]*std::sqrt(xx*rhomass*mdwidth)/denom;
   std::complex<double> bterm=par[3];
   std::complex<double> total=(aterm+bterm)*(aterm+bterm);
   double amptot=std::abs(total);

   double fff = std::abs(aterm)*std::abs(aterm);
   double amptwo = fff + std::abs(bterm)*std::abs(bterm);

   double res = amptot - amptwo;

   return res;
}

Double_t fdirect(Double_t *x, Double_t *par ) {
   return par[3]*par[3];
}

