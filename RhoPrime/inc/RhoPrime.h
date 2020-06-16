#pragma once
enum calc
{
    light,
    heavy,
    total,
    like,
    unlike,
    ptSig,
    ptTotal,
    ptBcg
};

class RhoPrime
{
public:
    RhoPrime(/* args */) = delete;
    static int netChargeValue;
        static calc variant;
    static bool isDebug;

    static TH1D Mass;
    static TH1D Pt;
}
