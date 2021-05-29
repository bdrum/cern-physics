# $\rho'$ analysis notes

## GIRD Selection criteria

These criteria were applied on the selection stage(GRID):

Events:

- \>= 4 tracks
    
Tracks:

- Has Point On inner OR outer ITS Layer
- Not ITS SA
- |dca1| < 3 && |dca0| < 3;

### Data info

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 110004 entries, 0 to 110003
    Data columns (total 49 columns):
     #   Column            Non-Null Count   Dtype  
    ---  ------            --------------   -----  
     0   RunNum            110004 non-null  int32  
     1   PeriodNumber      110004 non-null  int64  
     2   OrbitNumber       110004 non-null  int64  
     3   BunchCrossNumber  110004 non-null  int64  
     4   Mass              110004 non-null  float32
     5   Pt                110004 non-null  float32
     6   Q                 110004 non-null  int32  
     7   Rapidity          110004 non-null  float32
     8   Phi               110004 non-null  float32
     9   ZNAenergy         110004 non-null  float32
     10  ZNCenergy         110004 non-null  float32
     11  ZPAenergy         110004 non-null  float32
     12  ZPCenergy         110004 non-null  float32
     13  VtxX              110004 non-null  float32
     14  VtxY              110004 non-null  float32
     15  VtxZ              110004 non-null  float32
     16  VtxContrib        110004 non-null  int32  
     17  VtxChi2           110004 non-null  float32
     18  VtxNDF            110004 non-null  float32
     19  SpdVtxX           110004 non-null  float32
     20  SpdVtxY           110004 non-null  float32
     21  SpdVtxZ           110004 non-null  float32
     22  SpdVtxContrib     110004 non-null  int32  
     23  V0Adecision       110004 non-null  int32  
     24  V0Cdecision       110004 non-null  int32  
     25  ADAdecision       110004 non-null  int32  
     26  ADCdecision       110004 non-null  int32  
     27  V0Afired          110004 non-null  bool   
     28  V0Cfired          110004 non-null  bool   
     29  ADAfired          110004 non-null  bool   
     30  ADCfired          110004 non-null  bool   
     31  STPfired          110004 non-null  bool   
     32  SMBfired          110004 non-null  bool   
     33  SM2fired          110004 non-null  bool   
     34  SH1fired          110004 non-null  bool   
     35  OM2fired          110004 non-null  bool   
     36  OMUfired          110004 non-null  bool   
     37  IsTriggered       110004 non-null  bool   
     38  nTracklets        110004 non-null  int32  
     39  nTracks           110004 non-null  int32  
     40  ZDCAtime_0        110004 non-null  float32
     41  ZDCAtime_1        110004 non-null  float32
     42  ZDCAtime_2        110004 non-null  float32
     43  ZDCAtime_3        110004 non-null  float32
     44  ZDCCtime_0        110004 non-null  float32
     45  ZDCCtime_1        110004 non-null  float32
     46  ZDCCtime_2        110004 non-null  float32
     47  ZDCCtime_3        110004 non-null  float32
     48  FORChip           110004 non-null  object 
    dtypes: bool(11), float32(24), int32(10), int64(3), object(1)
    memory usage: 18.8+ MB
    <class 'pandas.core.frame.DataFrame'>
    MultiIndex: 26978093 entries, (0, 0) to (110003, 3)
    Data columns (total 13 columns):
     #   Column                  Dtype  
    ---  ------                  -----  
     0   T_NumberOfSigmaTPCPion  float32
     1   T_Eta                   float32
     2   T_Phi                   float32
     3   T_Px                    float32
     4   T_Py                    float32
     5   T_Pz                    float32
     6   T_Q                     int32  
     7   T_HasPointOnITSLayer0   bool   
     8   T_HasPointOnITSLayer1   bool   
     9   T_ITSModuleInner        int32  
     10  T_ITSModuleOuter        int32  
     11  T_TPCNCls               int32  
     12  T_TPCRefit              bool   
    dtypes: bool(3), float32(6), int32(4)
    memory usage: 1.2 GB
    

## Transverse momenta of initial data set


    
![png](4TracksAnalysis_files/4TracksAnalysis_3_0.png)
    


    C:\Users\bdrum\AppData\Roaming\Python\Python39\site-packages\mplhep\plot.py:238: RuntimeWarning: invalid value encountered in sqrt
      _yerr = np.sqrt(h)
    




    Text(0, 1, '#events / 20MeV')




    
![png](4TracksAnalysis_files/4TracksAnalysis_4_2.png)
    


## Analysis cuts

### Global tracks

It's known that global tracks consist from ITS and TPC identification, in our case we can implicitly add checks for TPC identification track and see what happens with the data.

Let's aply further conditions for the tracks:

* |NumberOfSigmaTPCPion| < 3
* Number of TPC Clusters > 50
* TPCRefit

## Low energy tracks and TPC

There is an idea about that tracks with small energies (low pt) not able to reach TPC.
Idea is that addding such condition will decrease our signal and background level.




    
![png](4TracksAnalysis_files/4TracksAnalysis_6_0.png)
    


As we can see above adding of gobal tracks will decrease statistics level, but it is correct for both signal and background. Let's estimate what number of global tracks in 4 tracks is enough:


    
![png](4TracksAnalysis_files/4TracksAnalysis_8_0.png)
    


Here we see such construction each row contains three plots:
 - starting point or what we have (first cell correspond our initial plot at the very begining of this notebook)
 - what we will throw
 - the difference between 1 and 2

 As we can see in case of transition from zero global tracks to one we will lose only background.
 I guess it's easy to see that the best case when we throw almost only background event is more than 2 global tracks in event.

 In further analysis I will be use this case. 'ITS & (>= 2TPC)'

## False triggering

There are some situations when CCUP9 trigger could be fired false:
It may occured when some fake or random track fires FOR and trigger will provide.

We can check list of FORs of event and what chipkey has each of four tracks.
In case it has matches and produce back to back topology this means correct trigger state.

![img](https://sun9-58.userapi.com/impf/x7UtIW5ElLKpDl4ASPuz0FXhNjwnxYcAy0BuHw/wJZr1On9l4o.jpg?size=1280x718&quality=96&sign=1ed3d5f08fcdefd89ab4e02a5041c6d0&type=album)

See debugging details in [one of the issue](https://github.com/bdrum/cern-physics/issues/42)


Let's do the same thing as we do few cell above and let's try to understand what we will throw after splitting event by fake triggered or not:


    
![png](4TracksAnalysis_files/4TracksAnalysis_12_0.png)
    



Let's see how looks masses for correct and fake trigger events:


    
![png](4TracksAnalysis_files/4TracksAnalysis_14_0.png)
    


As we can see above the shape of masses for fake trigger and correct trigger the same. Here we use pdf view for a normalization purposes. Despite of this fact we saw on $p_t$ distribution that fake triggers contains signal part, but most of the fake trigger data is bacgrkound events.

In further analysis we will use only correct trigger events. Also we hope that it will make our data closer to MC quality.

## ZDC cuts

ZDC again allows us to make signal more clear. Neutrons in ZDC could be a markers about peripheral events. 

    No handles with labels found to put in legend.
    


    
![png](4TracksAnalysis_files/4TracksAnalysis_17_1.png)
    


Beside energy distirbution we also have to make corrections for ZDC timing:

    No handles with labels found to put in legend.
    


    
![png](4TracksAnalysis_files/4TracksAnalysis_19_1.png)
    


Event called passed ZDC cuts if satisfied such criteria:
- For only one of the two sides
- neutrons energy less or equal than given parameter ZDC_En value
- or
- one of ZDC times not in an interval of +- ZDC_Time_Delta parameter value 


    
![png](4TracksAnalysis_files/4TracksAnalysis_21_0.png)
    


## Transversal momentum distribution after all cuts





    <matplotlib.legend.Legend at 0x252443f3430>




    
![png](4TracksAnalysis_files/4TracksAnalysis_23_1.png)
    


Now  let's try to see what tracks we lost from signal area and what contribution they have:

TPC and ITS has different coverage for polar angle:

![img1](https://camo.githubusercontent.com/9a7ab40d0f74a866a7095986644134a0f72cc58b/68747470733a2f2f70702e757365726170692e636f6d2f633835323231362f763835323231363738332f3131396137332f304f76685f6c544b4e7a552e6a7067)

Perhaps we have tracks that not only can't reach TPC, but also has $\theta$ values that TPC doesn't cover.

Below we can see polar angle distribution for tracks that covers three cases:

1. All tracks from events were reconstructed by ITS and TPC
2. Only ITS tracks from events with only part TPC tracks. Here tracks that not reconstructed by TPC
3. All tracks from events were reconstructed by ITS or TPC

We can see small gaps with for the second case, that allow to speak about correctness of the suggestion, but anyway low energy of tracks is the main reason why TPC can't reconstructed tracks.  

## Mass
Let's see on the mass distribution of the events





<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>count</th>
      <th>mean</th>
      <th>std</th>
      <th>min</th>
      <th>25%</th>
      <th>50%</th>
      <th>75%</th>
      <th>max</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>mass_ft_zq</th>
      <td>2418.0</td>
      <td>1.613113</td>
      <td>0.390436</td>
      <td>0.740946</td>
      <td>1.383315</td>
      <td>1.549550</td>
      <td>1.747386</td>
      <td>4.907002</td>
    </tr>
    <tr>
      <th>mass_ft_nzq</th>
      <td>663.0</td>
      <td>1.413462</td>
      <td>0.563853</td>
      <td>0.637530</td>
      <td>0.978157</td>
      <td>1.344274</td>
      <td>1.708745</td>
      <td>4.250375</td>
    </tr>
  </tbody>
</table>
</div>




    
![png](4TracksAnalysis_files/4TracksAnalysis_27_1.png)
    


### Pions subsystems

In our process 4 pions were producted. The most probably intermediate state including two pions and $\rho$ i.e.
$$\rho' \rightarrow \rho \ \pi^+ \pi^- \rightarrow \pi^+ \pi^- \pi^+ \pi^-$$ 

We can see this on distribution of mass that can be obtained as all combinations of pairs from intial four tracks, i.e. only four pairs:

![img](https://camo.githubusercontent.com/53a52e2a6d4ae7112d74f4073c979a51166170d8/68747470733a2f2f70702e757365726170692e636f6d2f633835333632342f763835333632343436372f34383466332f5431375a754b597062526f2e6a7067)

Here we can plot two distirbutions:

1. Make all possible(4) combinations of pairs. Then take lightest and pair that belong to one combination with that. Plot masses of these two pairs.
2. Plot masses of masses from possible combinations.




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>count</th>
      <th>mean</th>
      <th>std</th>
      <th>min</th>
      <th>25%</th>
      <th>50%</th>
      <th>75%</th>
      <th>max</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>heavy</th>
      <td>4836.0</td>
      <td>0.812236</td>
      <td>0.259066</td>
      <td>0.291725</td>
      <td>0.674686</td>
      <td>0.778129</td>
      <td>0.902377</td>
      <td>3.544038</td>
    </tr>
    <tr>
      <th>light</th>
      <td>4836.0</td>
      <td>0.525252</td>
      <td>0.164924</td>
      <td>0.279545</td>
      <td>0.399250</td>
      <td>0.498259</td>
      <td>0.627641</td>
      <td>2.129988</td>
    </tr>
  </tbody>
</table>
</div>




    
![png](4TracksAnalysis_files/4TracksAnalysis_30_1.png)
    


As we can see above, for second case (all possible pairs) we've got stronger signal in comparison with light-recoil pair as it made in [STAR work](http://arxiv.org/abs/0912.0604v2). Let's build 2d distirbuition and marginals component separately:

    No handles with labels found to put in legend.
    


    
![png](4TracksAnalysis_files/4TracksAnalysis_32_1.png)
    


## Data modeling
First of all let's try to fit $\rho(0)$ that we can see as heavy pair of final 4 pions state:

    No handles with labels found to put in legend.
    




    count    4836.000000
    mean        0.812236
    std         0.259066
    min         0.291725
    25%         0.674686
    50%         0.778129
    75%         0.902377
    max         3.544038
    Name: heavy, dtype: float64




    
![png](4TracksAnalysis_files/4TracksAnalysis_34_2.png)
    


    D:\GoogleDrive\Job\cern\Alice\analysis\dev\physics\notebooks\FourTracks\analysis\fit.py:22: RuntimeWarning: invalid value encountered in sqrt
      q = np.sqrt((x ** 2) / 4 - pi_pl_mass ** 2)
    D:\GoogleDrive\Job\cern\Alice\analysis\dev\physics\notebooks\FourTracks\analysis\fit.py:22: RuntimeWarning: invalid value encountered in sqrt
      q = np.sqrt((x ** 2) / 4 - pi_pl_mass ** 2)
    

    [[Model]]
        Model(bw)
    [[Fit Statistics]]
        # fitting method   = leastsq
        # function evals   = 25
        # data points      = 98
        # variables        = 3
        chi-square         = 109229.377
        reduced chi-square = 1149.78292
        Akaike info crit   = 693.591309
        Bayesian info crit = 701.346212
    ##  Warning: uncertainties could not be estimated:
        amp:  at initial value
    [[Variables]]
        M:    0.76953266 (init = 0.77)
        G:    0.44949013 (init = 0.45)
        amp:  100.000000 (init = 100)
    


    
![png](4TracksAnalysis_files/4TracksAnalysis_35_2.png)
    


    [[Model]]
        Model(bw_bckg)
    [[Fit Statistics]]
        # fitting method   = leastsq
        # function evals   = 26
        # data points      = 65
        # variables        = 4
        chi-square         = 9416.30433
        reduced chi-square = 154.365645
        Akaike info crit   = 331.427695
        Bayesian info crit = 340.125245
    ##  Warning: uncertainties could not be estimated:
        amp:       at initial value
    [[Variables]]
        M:         1.50025700 (init = 1.5)
        G:         0.44560648 (init = 0.45)
        amp:       90.0000000 (init = 90)
        amp_bckg:  1.04109842 (init = 0.2)
    


    
![png](4TracksAnalysis_files/4TracksAnalysis_36_1.png)
    


    [[Model]]
        (Model(bw_bckg, prefix='bw1_') + Model(bw_bckg, prefix='bw2_'))
    [[Fit Statistics]]
        # fitting method   = leastsq
        # function evals   = 70
        # data points      = 65
        # variables        = 8
        chi-square         = 7704.23934
        reduced chi-square = 135.162094
        Akaike info crit   = 326.384019
        Bayesian info crit = 343.779117
    ##  Warning: uncertainties could not be estimated:
        bw1_M:         at initial value
        bw1_G:         at initial value
        bw1_amp:       at initial value
        bw2_M:         at initial value
        bw2_G:         at initial value
        bw2_G:         at boundary
        bw2_amp:       at initial value
    [[Variables]]
        bw1_M:         1.45000000 (init = 1.45)
        bw1_G:         0.35000000 (init = 0.35)
        bw1_amp:       80.0000000 (init = 80)
        bw1_amp_bckg:  0.40223250 (init = 1)
        bw2_M:         1.65000000 (init = 1.65)
        bw2_G:         0.25000000 (init = 0.25)
        bw2_amp:       35.0000000 (init = 35)
        bw2_amp_bckg:  0.65405888 (init = 5)
    




    <matplotlib.legend.Legend at 0x25248e08be0>




    
![png](4TracksAnalysis_files/4TracksAnalysis_37_2.png)
    


    [[Model]]
        Model(polynomial)
    [[Fit Statistics]]
        # fitting method   = leastsq
        # function evals   = 18
        # data points      = 65
        # variables        = 5
        chi-square         = 827.353668
        reduced chi-square = 13.7892278
        Akaike info crit   = 175.349924
        Bayesian info crit = 186.221860
    ##  Warning: uncertainties could not be estimated:
        c0:  at initial value
        c1:  at initial value
        c2:  at initial value
        c3:  at initial value
        c4:  at initial value
    [[Variables]]
        c0: -52.0214731 (init = -52.02159)
        c1:  158.952975 (init = 158.9533)
        c2: -125.475867 (init = -125.4759)
        c3:  38.7143145 (init = 38.71442)
        c4: -4.22387924 (init = -4.223879)
    




    [<matplotlib.lines.Line2D at 0x25248759670>]




    
![png](4TracksAnalysis_files/4TracksAnalysis_38_2.png)
    


    [[Model]]
        ((Model(bw, prefix='bw1_') + Model(bw, prefix='bw2_')) + Model(polynomial, prefix='bckg_'))
    [[Fit Statistics]]
        # fitting method   = leastsq
        # function evals   = 24
        # data points      = 65
        # variables        = 11
        chi-square         = 11899.3006
        reduced chi-square = 220.357418
        Akaike info crit   = 360.640096
        Bayesian info crit = 384.558356
    ##  Warning: uncertainties could not be estimated:
        bw1_M:    at initial value
        bw1_G:    at initial value
        bw1_amp:  at initial value
        bw2_M:    at initial value
        bw2_G:    at initial value
        bw2_amp:  at initial value
        bckg_c0:  at initial value
        bckg_c1:  at initial value
        bckg_c2:  at initial value
        bckg_c3:  at initial value
        bckg_c4:  at initial value
    [[Variables]]
        bw1_M:    1.50000000 (init = 1.5)
        bw1_G:    0.40000000 (init = 0.4)
        bw1_amp:  85.0000000 (init = 85)
        bw2_M:    1.65000000 (init = 1.65)
        bw2_G:    0.20000000 (init = 0.2)
        bw2_amp:  15.0000000 (init = 15)
        bckg_c0: -34.8419011 (init = -34.8419)
        bckg_c1:  105.895125 (init = 105.8951)
        bckg_c2: -83.9664919 (init = -83.96649)
        bckg_c3:  26.1691031 (init = 26.1691)
        bckg_c4: -2.90076667 (init = -2.900767)
    


    
![png](4TracksAnalysis_files/4TracksAnalysis_39_1.png)
    


## Decay angle for $\rho_0$

Here we would like to study angle decay for $\rho_0 \rightarrow \pi^+\pi^-$ between the momentum of one of the pions in the rest frame of $\rho_0$ and original(lab frame) momentum of  $\rho_0$.

For the sake of simplicity first we will create new lab system with OZ axis directed along momentum of $\rho_0$ in lab frame.

The transition from original lab frame to the new one could be obtain by two rotation:

- First, around x axis:

Rotation matrix for this case:
$$
R_{x,\alpha}=
\Bigg(
\begin{matrix}
1 & 0 & 0\\
0 & \cos{\alpha} & -\sin{\alpha} \\
0 & \sin{\alpha} & \cos{\alpha}
\end{matrix}
\Bigg)
$$

Rotation angle for x axis:

$$
\begin{matrix}
\sin{\alpha} =  \frac{p_y}{\sqrt{p_y^2+p_z^2}}  \\
\cos{\alpha} =  \frac{p_z}{\sqrt{p_y^2+p_z^2}}  \\
\end{matrix}
$$

Now, momentum vector of $\rho_0$ in this system will looks like

$$
\boldsymbol{p'}=R_{x,\alpha}\boldsymbol{p}=
\Bigg(
\begin{matrix}
p_x\\
p_y\cos{\alpha} - p_z\sin{\alpha}\\
p_y\sin{\alpha} + p_z\cos{\alpha})
\end{matrix}
\Bigg)
$$


- Second, around y axis:

Rotation matrix for this case will looks like
$$
R = R_{y,-\beta}= 
\Bigg(
\begin{matrix}
\cos{\beta} & 0 & -\sin{\beta}\\
0 & 1 & 0 \\
\sin{\beta} & 0 & \cos{\beta}
\end{matrix}
\Bigg)
$$

We have to apply it for already rotated vector around x axis:


$$
\boldsymbol{p''} =R_{y,-\beta}\boldsymbol{p'} = 
\Bigg(
\begin{matrix}
\cos{\beta} & 0 & -\sin{\beta}\\
0 & 1 & 0 \\
\sin{\beta} & 0 & \cos{\beta}
\end{matrix}
\Bigg)
\Bigg(
\begin{matrix}
{p'}_x\\
{p'}_y\\
{p'}_z
\end{matrix}
\Bigg)
 = 
\Bigg(
\begin{matrix}
{p'}_x\cos{\beta}-{p'}_z\sin{\beta}\\
{p'}_y\\
{p'}_x\sin{\beta}+{p'}_z\cos{\beta}
\end{matrix}
\Bigg)
$$


Where rotation angle based on the new rotated vector $\boldsymbol{p'}$ coordinates:

$$
\begin{matrix}
\sin{\beta}  =  \frac{{p'}_x}{\sqrt{{p'_x}^2+{p'}_z^2}}  \\
\cos{\beta}  =  \frac{{p'}_z}{\sqrt{{p'_x}^2+{p'}_z^2}}  \\
\end{matrix}
$$

As a result final transition looks like:
_____________
$$
\boldsymbol{p''} =
\Bigg(
\begin{matrix}
{p'}_x\cos{\beta}-{p'}_z\sin{\beta}\\
{p'}_y\\
{p'}_x\sin{\beta}+{p'}_z\cos{\beta}
\end{matrix}
\Bigg)=
\Bigg(
\begin{matrix}
p_x\cos{\beta}-p_y\sin{\alpha}\sin{\beta}-p_z\cos{\alpha}\sin{\beta} \\
p_y\cos{\alpha}-p_z\sin{\alpha} \\
p_x\sin{\beta}+p_y\sin{\alpha}\cos{\beta}+p_z\cos{\alpha}\cos{\beta}
\end{matrix}
\Bigg)
$$
where rotation angles are:


$$
\begin{matrix}
\sin{\alpha} =  \frac{p_y}{\sqrt{p_y^2+p_z^2}}  \\
\cos{\alpha} =  \frac{p_z}{\sqrt{p_y^2+p_z^2}}  \\
\sin{\beta}  =  \frac{p_x}{\sqrt{p_x^2+(p_y\sin{\alpha}+p_z\cos{\alpha})^2}}  \\
\cos{\beta}  =  \frac{p_y\sin{\alpha}+p_z\cos{\alpha}}{\sqrt{p_x^2+(p_y\sin{\alpha}+p_z\cos{\alpha})^2}}  \\
\end{matrix}
$$


Now let's consider moving coordinate system with $\rho_0$ so that OZ axis direct along $\boldsymbol{p}_{\rho_0}$

We know components of original momentum of $\pi^+$ in the such system and now let's boost their via Lorentz Transormation:

$$
\begin{matrix}
\ {E'} =  \gamma E - \Gamma p_z \\
\ {p'}_x= p_x \\
\ {p'}_y= p_y \\
\ {p'}_z= \gamma p_z - \Gamma E \\
\end{matrix}
$$

where 
$$ \boldsymbol{\beta} = \frac{\boldsymbol{p}}{E} $$
$$ \gamma = \frac{E}{m}$$
$$ \Gamma = \gamma \beta = \frac{p}{m}$$


$$ \boldsymbol{\beta} = \frac{\boldsymbol{p}}{E} $$
$$ \gamma = \frac{1}{\sqrt{1-\frac{p^2}{E^2}}}$$

Now the searched angle can be obtain from scalar multiplication of $\pi^+$ momentum in the rest frame of $\rho_0$ and momentum of $\rho_0$ in the lab frame:

$$\cos{\theta}=\frac{\boldsymbol{{p'}_{\pi^+}}\boldsymbol{p_{\rho_0}}} {{p'}_{\pi^+}p_{\rho_0}}$$

## Cross section

Let's see to cross section of my events.

For this we should take luminosity of runs.

> Unfortunately file that I have to use for getting luminosity have a reference to special class AliTriggerInfo and moreover it packed into TObjArray, so I can't read it via uproot4. This is the reason why I used pure root again. [Here is the script](https://github.com/bdrum/cern-physics/blob/master/root-cpp/RhoPrime/macro/lumi.C) that I used.

Then let's see how much events do we have in each run.

$$L = \frac{1}{\sigma} \frac{\delta N}{\delta t}$$, this means that 

$$\sigma \approx \frac{N}{L}$$

Cross section of phenomena should be flat and independent from runs. 

Let's check it:




    count    117.000000
    mean       3.555185
    std        1.101315
    min        0.716081
    25%        2.823498
    50%        3.477399
    75%        4.276723
    max        6.551968
    Name: sigma, dtype: float64




    
![png](4TracksAnalysis_files/4TracksAnalysis_44_0.png)
    


## Other decays

In PDG I've seen also other interesting modes for $\rho'$:

- 1. $\rho' \rightarrow \eta_0 \rho_0$ | ?
   - 1.1. $\rho_0 \rightarrow 4 \pi$ | $2*10^{-5}\%$
   - 1.2. $\rho_0 \rightarrow \pi^+ \pi^-$ | $10^{-2}\%$
   - 1.3. $\eta_0' \rightarrow  \pi^+ \pi^- \gamma$ | $4\%$
   - 1.4. $\eta_0' \rightarrow  \pi^+ \pi^- \pi^0$ | $23\%$
- 2. $\rho' \rightarrow 4 \pi$ | ?

What if $\rho' \rightarrow \rho_0 \rho_0$ possible?
