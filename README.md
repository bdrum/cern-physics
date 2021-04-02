# $\rho'$ analysis notes

## GIRD Selection criteria:

These criteria were applied on the selection stage(GRID):

Events:

- \>= 4 tracks
    
Tracks:

- Has Point On inner OR outer ITS Layer
- Not ITS SA
- |dca1| < 3 && |dca0| < 3;

### Data info

    Events attributes:
    ['RunNum', 'PeriodNumber', 'OrbitNumber', 'BunchCrossNumber', 'Mass', 'Pt', 'Q', 'Rapidity', 'Phi', 'ZNAenergy', 'ZNCenergy', 'ZPAenergy', 'ZPCenergy', 'VtxX', 'VtxY', 'VtxZ', 'VtxContrib', 'VtxChi2', 'VtxNDF', 'SpdVtxX', 'SpdVtxY', 'SpdVtxZ', 'SpdVtxContrib', 'V0Adecision', 'V0Cdecision', 'ADAdecision', 'ADCdecision', 'V0Afired', 'V0Cfired', 'ADAfired', 'ADCfired', 'STPfired', 'SMBfired', 'SM2fired', 'SH1fired', 'OM2fired', 'OMUfired', 'IsTriggered', 'nTracklets', 'nTracks', 'FORChip']
    Track attributes:
    ['T_NumberOfSigmaTPCPion', 'T_Eta', 'T_Phi', 'T_Px', 'T_Py', 'T_Pz', 'T_Q', 'T_HasPointOnITSLayer0', 'T_HasPointOnITSLayer1', 'T_ITSModuleInner', 'T_ITSModuleOuter', 'T_TPCNCls', 'T_TPCRefit']
    
    Events count: 106,705
    Tracks count: 25,117,847
    

## Analysis criteria

Let's take from input date only events with 4 tracks and zero total charge.
Also prepare mask for tracks that satisfy standatd criteria contains further conditions for the TPC:

* |NumberOfSigmaTPCPion| < 3
* Number of TPC Clusters > 50
* TPCRefit
## Low energy tracks and TPC

There is an idea about that tracks with small energies (low pt) not able to reach TPC.
We can try to estimate influence of TPC criteria to the statistics.

Let's see what happend in case of we will plot pt for any combination of TPC tracks:

### Event with std criteria

|detector|track1|track2|track3|track4|
|:--:|:--:|:--:|:--:|:--:|
|ITS|+|+|+|+|
|TPC|+|+|+|+|

### Let's start to take also such combinations to the sample:

|detector|track1|track2|track3|track4|
|:--:|:--:|:--:|:--:|:--:|
|ITS|+|+|+|+|
|TPC|+|+|+|-|

|detector|track1|track2|track3|track4|
|:--:|:--:|:--:|:--:|:--:|
|ITS|+|+|+|+|
|TPC|+|+|-|-|

|detector|track1|track2|track3|track4|
|:--:|:--:|:--:|:--:|:--:|
|ITS|+|+|+|+|
|TPC|+|-|-|-|

|detector|track1|track2|track3|track4|
|:--:|:--:|:--:|:--:|:--:|
|ITS|+|+|+|+|
|TPC|-|-|-|-|

We can see statistics gain ration equal 2.5 between std criteria and total combinations:


## False triggering

There are some situations when CCUP9 trigger could be fired false:
It may occured when some fake or random track fires FOR and trigger will provide.

We can check list of FORs of event and what chipkey has each of four tracks.
In case it has matches and produce back to back topology this means correct trigger state.

![img](https://sun9-58.userapi.com/impf/x7UtIW5ElLKpDl4ASPuz0FXhNjwnxYcAy0BuHw/wJZr1On9l4o.jpg?size=1280x718&quality=96&sign=1ed3d5f08fcdefd89ab4e02a5041c6d0&type=album)

See debugging details in [one of the issue](https://github.com/bdrum/cern-physics/issues/42)


      0%|          | 0/76776 [00:00<?, ?it/s]<ipython-input-3-c6feb8d2429e>:36: SettingWithCopyWarning: 
    A value is trying to be set on a copy of a slice from a DataFrame
    
    See the caveats in the documentation: https://pandas.pydata.org/pandas-docs/stable/user_guide/indexing.html#returning-a-view-versus-a-copy
      df.vPhiInner[i] = vPhiInner1
    <ipython-input-3-c6feb8d2429e>:39: SettingWithCopyWarning: 
    A value is trying to be set on a copy of a slice from a DataFrame
    
    See the caveats in the documentation: https://pandas.pydata.org/pandas-docs/stable/user_guide/indexing.html#returning-a-view-versus-a-copy
      df.vPhiOuter[i] = vPhiOuter1
    <ipython-input-3-c6feb8d2429e>:41: SettingWithCopyWarning: 
    A value is trying to be set on a copy of a slice from a DataFrame
    
    See the caveats in the documentation: https://pandas.pydata.org/pandas-docs/stable/user_guide/indexing.html#returning-a-view-versus-a-copy
      df.vPhiInnerValue[i] = vPhiInnerValues
    <ipython-input-3-c6feb8d2429e>:42: SettingWithCopyWarning: 
    A value is trying to be set on a copy of a slice from a DataFrame
    
    See the caveats in the documentation: https://pandas.pydata.org/pandas-docs/stable/user_guide/indexing.html#returning-a-view-versus-a-copy
      df.vPhiOuterValue[i] = vPhiOuterValues
    100%|██████████| 76776/76776 [04:50<00:00, 264.48it/s]
    100%|██████████| 19194/19194 [00:10<00:00, 1816.33it/s]
    

### Trigger share




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
      <th>nTPC</th>
      <th>total_cnt</th>
      <th>trig_cnt</th>
      <th>untrig_cnt</th>
      <th>trig % from ttl</th>
      <th>untrig % from ttl</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>0</td>
      <td>19194</td>
      <td>10349</td>
      <td>8845</td>
      <td>53.9</td>
      <td>46.1</td>
    </tr>
    <tr>
      <th>1</th>
      <td>1</td>
      <td>17641</td>
      <td>10138</td>
      <td>7503</td>
      <td>57.5</td>
      <td>42.5</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2</td>
      <td>16506</td>
      <td>9572</td>
      <td>6934</td>
      <td>58.0</td>
      <td>42.0</td>
    </tr>
    <tr>
      <th>3</th>
      <td>3</td>
      <td>12952</td>
      <td>7583</td>
      <td>5369</td>
      <td>58.5</td>
      <td>41.5</td>
    </tr>
    <tr>
      <th>4</th>
      <td>4</td>
      <td>5916</td>
      <td>3506</td>
      <td>2410</td>
      <td>59.3</td>
      <td>40.7</td>
    </tr>
  </tbody>
</table>
</div>



## Transversal momentum distribution

We can see what happend in case of we will make criteria for TPC softer, i.e. not each of four tracks
should be TPC refitted, but only 3 etc.


    Canvas(toolbar=Toolbar(toolitems=[('Home', 'Reset original view', 'home', 'home'), ('Back', 'Back to previous …





    
![svg](4TracksAnalysis_files/4TracksAnalysis_9_1.svg)
    



Let' see what exactly gain we have in the same order:

0TPC - 1TPC

...

    Warning in <TCanvas::Constructor>: Deleting canvas with same name: c_sg
    Warning in <TROOT::Append>: Replacing existing TH1: ft_zq_Pt_nTpc[4] (Potential memory leak).
    Warning in <TROOT::Append>: Replacing existing TH1: ft_zq_Pt_nTpc[4] (Potential memory leak).
    Warning in <TROOT::Append>: Replacing existing TH1: ft_nzq_Pt_nTpc[4] (Potential memory leak).
    Warning in <TROOT::Append>: Replacing existing TH1: ft_zq_Pt_nTpc[4] (Potential memory leak).
    Warning in <TROOT::Append>: Replacing existing TH1: ft_nzq_Pt_nTpc[4] (Potential memory leak).
    Warning in <TROOT::Append>: Replacing existing TH1: ft_zq_Pt_nTpc[4] (Potential memory leak).
    Warning in <TROOT::Append>: Replacing existing TH1: ft_nzq_Pt_nTpc[4] (Potential memory leak).
    



<div id="root_plot_1617292798985"
     style="width: 396px; height: 772px">
</div>
<script>
if (typeof require !== 'undefined') {

    // All requirements met (we are in jupyter notebooks or we loaded requirejs before).
    display_root_plot_1617292798985();

} else {

    // We are in jupyterlab, we need to insert requirejs and configure it.
    // Jupyterlab might be installed in a different base_url so we need to know it.
    try {
        var base_url = JSON.parse(document.getElementById('jupyter-config-data').innerHTML).baseUrl;
    } catch(_) {
        var base_url = '/';
    }

    // Try loading a local version of requirejs and fallback to cdn if not possible.
    requirejs_load(base_url + 'static/components/requirejs/require.js', requirejs_success(base_url), function(){
        requirejs_load('https://cdnjs.cloudflare.com/ajax/libs/require.js/2.2.0/require.min.js', requirejs_success(base_url), function(){
            document.getElementById("root_plot_1617292798985").innerHTML = "Failed to load requireJs";
        });
    });
}

function requirejs_load(src, on_load, on_error) {
    var script = document.createElement('script');
    script.src = src;
    script.onload = on_load;
    script.onerror = on_error;
    document.head.appendChild(script);
}

function requirejs_success(base_url) {
    return function() {
        require.config({
            baseUrl: base_url + 'static/'
        });
        display_root_plot_1617292798985();
    }
}

function display_root_plot_1617292798985() {
    require(['scripts/JSRootCore'],
        function(Core) {
            var obj = Core.JSONR_unref({"_typename":"TCanvas","fUniqueID":0,"fBits":3342344,"fLineColor":1,"fLineStyle":1,"fLineWidth":1,"fFillColor":0,"fFillStyle":1001,"fLeftMargin":0.1,"fRightMargin":0.1,"fBottomMargin":0.1,"fTopMargin":0.1,"fXfile":2,"fYfile":2,"fAfile":1,"fXstat":0.99,"fYstat":0.99,"fAstat":2,"fFrameFillColor":0,"fFrameLineColor":1,"fFrameFillStyle":1001,"fFrameLineStyle":1,"fFrameLineWidth":1,"fFrameBorderSize":1,"fFrameBorderMode":0,"fX1":0,"fY1":0,"fX2":1,"fY2":1,"fXtoAbsPixelk":5e-5,"fXtoPixelk":5e-5,"fXtoPixel":396,"fYtoAbsPixelk":772.00005,"fYtoPixelk":772.00005,"fYtoPixel":-772,"fUtoAbsPixelk":5e-5,"fUtoPixelk":5e-5,"fUtoPixel":396,"fVtoAbsPixelk":772.00005,"fVtoPixelk":772,"fVtoPixel":-772,"fAbsPixeltoXk":0,"fPixeltoXk":0,"fPixeltoX":0.00252525252525253,"fAbsPixeltoYk":1,"fPixeltoYk":0,"fPixeltoY":-0.00129533678756477,"fXlowNDC":0,"fYlowNDC":0,"fXUpNDC":1,"fYUpNDC":1,"fWNDC":1,"fHNDC":1,"fAbsXlowNDC":0,"fAbsYlowNDC":0,"fAbsWNDC":1,"fAbsHNDC":1,"fUxmin":0,"fUymin":0,"fUxmax":1,"fUymax":1,"fTheta":30,"fPhi":30,"fAspectRatio":0,"fNumber":0,"fTickx":0,"fTicky":0,"fLogx":0,"fLogy":0,"fLogz":0,"fPadPaint":0,"fCrosshair":0,"fCrosshairPos":0,"fBorderSize":2,"fBorderMode":0,"fModified":false,"fGridx":false,"fGridy":false,"fAbsCoord":false,"fEditable":true,"fFixedAspectRatio":false,"fPrimitives":{"_typename":"TList","name":"TList","arr":[{"_typename":"TPad","fUniqueID":0,"fBits":9,"fLineColor":1,"fLineStyle":1,"fLineWidth":1,"fFillColor":0,"fFillStyle":1001,"fLeftMargin":0.1,"fRightMargin":0.1,"fBottomMargin":0.1,"fTopMargin":0.1,"fXfile":2,"fYfile":2,"fAfile":1,"fXstat":0.99,"fYstat":0.99,"fAstat":2,"fFrameFillColor":0,"fFrameLineColor":1,"fFrameFillStyle":1001,"fFrameLineStyle":1,"fFrameLineWidth":1,"fFrameBorderSize":1,"fFrameBorderMode":0,"fX1":-0.250000018626453,"fY1":-63.3937547232027,"fX2":2.25000001862645,"fY2":570.543754723203,"fXtoAbsPixelk":42.7680522423268,"fXtoPixelk":38.8080523308397,"fXtoPixel":155.231997757673,"fYtoAbsPixelk":167.524049079704,"fYtoPixelk":159.80404925226,"fYtoPixel":-0.280090699318562,"fUtoAbsPixelk":3.9600499114871,"fUtoPixelk":5e-5,"fUtoPixel":388.080000177026,"fVtoAbsPixelk":185.280050172555,"fVtoPixelk":177.560000345111,"fVtoPixel":-177.560000345111,"fAbsPixeltoXk":-0.275510222506383,"fPixeltoXk":-0.250000018626453,"fPixeltoX":0.00644197082073931,"fAbsPixeltoYk":598.106254464275,"fPixeltoYk":-63.3937547232027,"fPixeltoY":-3.5702720669873,"fXlowNDC":0.00999999977648258,"fYlowNDC":0.759999999776483,"fXUpNDC":0.990000000223517,"fYUpNDC":0.990000000223517,"fWNDC":0.980000000447035,"fHNDC":0.230000000447035,"fAbsXlowNDC":0.00999999977648258,"fAbsYlowNDC":0.759999999776483,"fAbsWNDC":0.980000000447035,"fAbsHNDC":0.230000000447035,"fUxmin":0,"fUymin":0,"fUxmax":2,"fUymax":507.15,"fTheta":30,"fPhi":30,"fAspectRatio":0,"fNumber":1,"fTickx":0,"fTicky":0,"fLogx":0,"fLogy":0,"fLogz":0,"fPadPaint":0,"fCrosshair":0,"fCrosshairPos":0,"fBorderSize":2,"fBorderMode":0,"fModified":false,"fGridx":false,"fGridy":false,"fAbsCoord":false,"fEditable":true,"fFixedAspectRatio":false,"fPrimitives":{"_typename":"TList","name":"TList","arr":[{"_typename":"TFrame","fUniqueID":0,"fBits":8,"fLineColor":1,"fLineStyle":1,"fLineWidth":1,"fFillColor":0,"fFillStyle":1001,"fX1":0,"fY1":0,"fX2":2,"fY2":507.15,"fBorderSize":1,"fBorderMode":0},{"_typename":"TH1D","fUniqueID":0,"fBits":521,"fName":"ft_zq_Pt_nTpc[0]_copy","fTitle":"ft_zq_Pt_nTpc[0]","fLineColor":1,"fLineStyle":1,"fLineWidth":1,"fFillColor":0,"fFillStyle":1001,"fMarkerColor":1,"fMarkerStyle":8,"fMarkerSize":1,"fNcells":102,"fXaxis":{"_typename":"TAxis","fUniqueID":0,"fBits":0,"fName":"xaxis","fTitle":"","fNdivisions":510,"fAxisColor":1,"fLabelColor":1,"fLabelFont":42,"fLabelOffset":0.005,"fLabelSize":0.035,"fTickLength":0.03,"fTitleOffset":1,"fTitleSize":0.035,"fTitleColor":1,"fTitleFont":42,"fNbins":100,"fXmin":0,"fXmax":2,"fXbins":[],"fFirst":0,"fLast":0,"fBits2":0,"fTimeDisplay":false,"fTimeFormat":"","fLabels":null,"fModLabs":null},"fYaxis":{"_typename":"TAxis","fUniqueID":0,"fBits":0,"fName":"yaxis","fTitle":"","fNdivisions":510,"fAxisColor":1,"fLabelColor":1,"fLabelFont":42,"fLabelOffset":0.005,"fLabelSize":0.035,"fTickLength":0.03,"fTitleOffset":1,"fTitleSize":0.035,"fTitleColor":1,"fTitleFont":42,"fNbins":1,"fXmin":0,"fXmax":1,"fXbins":[],"fFirst":0,"fLast":0,"fBits2":0,"fTimeDisplay":false,"fTimeFormat":"","fLabels":null,"fModLabs":null},"fZaxis":{"_typename":"TAxis","fUniqueID":0,"fBits":0,"fName":"zaxis","fTitle":"","fNdivisions":510,"fAxisColor":1,"fLabelColor":1,"fLabelFont":42,"fLabelOffset":0.005,"fLabelSize":0.035,"fTickLength":0.03,"fTitleOffset":1,"fTitleSize":0.035,"fTitleColor":1,"fTitleFont":42,"fNbins":1,"fXmin":0,"fXmax":1,"fXbins":[],"fFirst":0,"fLast":0,"fBits2":0,"fTimeDisplay":false,"fTimeFormat":"","fLabels":null,"fModLabs":null},"fBarOffset":0,"fBarWidth":1000,"fEntries":12736,"fTsumw":12736,"fTsumw2":12736,"fTsumwx":7175.9,"fTsumwx2":6426.7112,"fMaximum":-1111,"fMinimum":-1111,"fNormFactor":0,"fContour":[],"fSumw2":[],"fOption":"","fFunctions":{"_typename":"TList","name":"TList","arr":[],"opt":[]},"fBufferSize":0,"fBuffer":[],"fBinStatErrOpt":0,"fStatOverflows":2,"fArray":[0,201,471,483,339,262,214,242,186,206,237,231,250,247,264,255,296,297,270,268,245,250,254,212,235,231,212,246,215,204,216,248,189,201,187,179,169,167,155,188,140,144,122,128,136,122,110,113,94,99,96,80,94,101,84,65,73,86,60,66,64,62,70,54,47,45,41,57,43,31,48,37,49,47,45,23,26,27,28,38,31,35,20,22,26,27,19,21,21,22,20,20,15,23,17,14,10,13,18,13,12,542]}],"opt":["",""]},"fExecs":{"_typename":"TList","name":"TList","arr":[],"opt":[]},"fName":"c_sg_1","fTitle":"c_sg_1","fNumPaletteColor":0,"fNextPaletteColor":0},{"_typename":"TPad","fUniqueID":0,"fBits":9,"fLineColor":1,"fLineStyle":1,"fLineWidth":1,"fFillColor":0,"fFillStyle":1001,"fLeftMargin":0.1,"fRightMargin":0.1,"fBottomMargin":0.1,"fTopMargin":0.1,"fXfile":2,"fYfile":2,"fAfile":1,"fXstat":0.99,"fYstat":0.99,"fAstat":2,"fFrameFillColor":0,"fFrameLineColor":1,"fFrameFillStyle":1001,"fFrameLineStyle":1,"fFrameLineWidth":1,"fFrameBorderSize":1,"fFrameBorderMode":0,"fX1":-0.250000018626453,"fY1":-61.8187546058561,"fX2":2.25000001862645,"fY2":556.368754605856,"fXtoAbsPixelk":42.7680522423268,"fXtoPixelk":38.8080523308397,"fXtoPixel":155.231997757673,"fYtoAbsPixelk":360.524049079704,"fYtoPixelk":159.80404925226,"fYtoPixel":-0.287226768091009,"fUtoAbsPixelk":3.9600499114871,"fUtoPixelk":5e-5,"fUtoPixel":388.080000177026,"fVtoAbsPixelk":378.280050172555,"fVtoPixelk":177.560000345111,"fVtoPixel":-177.560000345111,"fAbsPixeltoXk":-0.275510222506383,"fPixeltoXk":-0.250000018626453,"fPixeltoX":0.00644197082073931,"fAbsPixeltoYk":1255.189415234,"fPixeltoYk":-61.8187546058561,"fPixeltoY":-3.48156965538513,"fXlowNDC":0.00999999977648258,"fYlowNDC":0.509999999776483,"fXUpNDC":0.990000000223517,"fYUpNDC":0.740000000223517,"fWNDC":0.980000000447035,"fHNDC":0.230000000447035,"fAbsXlowNDC":0.00999999977648258,"fAbsYlowNDC":0.509999999776483,"fAbsWNDC":0.980000000447035,"fAbsHNDC":0.230000000447035,"fUxmin":0,"fUymin":0,"fUxmax":2,"fUymax":494.55,"fTheta":30,"fPhi":30,"fAspectRatio":0,"fNumber":2,"fTickx":0,"fTicky":0,"fLogx":0,"fLogy":0,"fLogz":0,"fPadPaint":0,"fCrosshair":0,"fCrosshairPos":0,"fBorderSize":2,"fBorderMode":0,"fModified":false,"fGridx":false,"fGridy":false,"fAbsCoord":false,"fEditable":true,"fFixedAspectRatio":false,"fPrimitives":{"_typename":"TList","name":"TList","arr":[{"_typename":"TFrame","fUniqueID":0,"fBits":8,"fLineColor":1,"fLineStyle":1,"fLineWidth":1,"fFillColor":0,"fFillStyle":1001,"fX1":0,"fY1":0,"fX2":2,"fY2":494.55,"fBorderSize":1,"fBorderMode":0},{"_typename":"TH1D","fUniqueID":0,"fBits":521,"fName":"ft_zq_Pt_nTpc[1]_copy","fTitle":"ft_zq_Pt_nTpc[1]","fLineColor":1,"fLineStyle":1,"fLineWidth":1,"fFillColor":0,"fFillStyle":1001,"fMarkerColor":1,"fMarkerStyle":8,"fMarkerSize":1,"fNcells":102,"fXaxis":{"_typename":"TAxis","fUniqueID":0,"fBits":0,"fName":"xaxis","fTitle":"","fNdivisions":510,"fAxisColor":1,"fLabelColor":1,"fLabelFont":42,"fLabelOffset":0.005,"fLabelSize":0.035,"fTickLength":0.03,"fTitleOffset":1,"fTitleSize":0.035,"fTitleColor":1,"fTitleFont":42,"fNbins":100,"fXmin":0,"fXmax":2,"fXbins":[],"fFirst":0,"fLast":0,"fBits2":0,"fTimeDisplay":false,"fTimeFormat":"","fLabels":null,"fModLabs":null},"fYaxis":{"_typename":"TAxis","fUniqueID":0,"fBits":0,"fName":"yaxis","fTitle":"","fNdivisions":510,"fAxisColor":1,"fLabelColor":1,"fLabelFont":42,"fLabelOffset":0.005,"fLabelSize":0.035,"fTickLength":0.03,"fTitleOffset":1,"fTitleSize":0.035,"fTitleColor":1,"fTitleFont":42,"fNbins":1,"fXmin":0,"fXmax":1,"fXbins":[],"fFirst":0,"fLast":0,"fBits2":0,"fTimeDisplay":false,"fTimeFormat":"","fLabels":null,"fModLabs":null},"fZaxis":{"_typename":"TAxis","fUniqueID":0,"fBits":0,"fName":"zaxis","fTitle":"","fNdivisions":510,"fAxisColor":1,"fLabelColor":1,"fLabelFont":42,"fLabelOffset":0.005,"fLabelSize":0.035,"fTickLength":0.03,"fTitleOffset":1,"fTitleSize":0.035,"fTitleColor":1,"fTitleFont":42,"fNbins":1,"fXmin":0,"fXmax":1,"fXbins":[],"fFirst":0,"fLast":0,"fBits2":0,"fTimeDisplay":false,"fTimeFormat":"","fLabels":null,"fModLabs":null},"fBarOffset":0,"fBarWidth":1000,"fEntries":11390,"fTsumw":11390,"fTsumw2":11390,"fTsumwx":6279.6,"fTsumwx2":5552.6486,"fMaximum":-1111,"fMinimum":-1111,"fNormFactor":0,"fContour":[],"fSumw2":[],"fOption":"","fFunctions":{"_typename":"TList","name":"TList","arr":[],"opt":[]},"fBufferSize":0,"fBuffer":[],"fBinStatErrOpt":0,"fStatOverflows":2,"fArray":[0,192,457,471,324,249,194,219,170,182,220,198,218,224,238,225,258,272,241,237,214,222,231,187,214,203,180,219,184,185,189,226,172,181,172,151,149,151,139,163,122,123,108,107,119,104,104,96,82,91,84,68,84,87,76,59,65,78,55,58,55,54,55,47,41,36,39,49,40,25,42,32,45,36,40,17,20,26,22,33,30,29,16,18,19,22,14,20,19,20,15,18,15,17,12,11,9,8,14,11,8,335]}],"opt":["",""]},"fExecs":{"_typename":"TList","name":"TList","arr":[],"opt":[]},"fName":"c_sg_2","fTitle":"c_sg_2","fNumPaletteColor":0,"fNextPaletteColor":0},{"_typename":"TPad","fUniqueID":0,"fBits":9,"fLineColor":1,"fLineStyle":1,"fLineWidth":1,"fFillColor":0,"fFillStyle":1001,"fLeftMargin":0.1,"fRightMargin":0.1,"fBottomMargin":0.1,"fTopMargin":0.1,"fXfile":2,"fYfile":2,"fAfile":1,"fXstat":0.99,"fYstat":0.99,"fAstat":2,"fFrameFillColor":0,"fFrameLineColor":1,"fFrameFillStyle":1001,"fFrameLineStyle":1,"fFrameLineWidth":1,"fFrameBorderSize":1,"fFrameBorderMode":0,"fX1":-0.250000018626453,"fY1":-58.5375043613839,"fX2":2.25000001862645,"fY2":526.837504361384,"fXtoAbsPixelk":42.7680522423268,"fXtoPixelk":38.8080523308397,"fXtoPixel":155.231997757673,"fYtoAbsPixelk":553.524049079704,"fYtoPixelk":159.80404925226,"fYtoPixel":-0.303326923253061,"fUtoAbsPixelk":3.9600499114871,"fUtoPixelk":5e-5,"fUtoPixel":388.080000177026,"fVtoAbsPixelk":571.280050172555,"fVtoPixelk":177.560000345111,"fVtoPixel":-177.560000345111,"fAbsPixeltoXk":-0.275510222506383,"fPixeltoXk":-0.250000018626453,"fPixeltoX":0.00644197082073931,"fAbsPixeltoYk":1824.84295539406,"fPixeltoYk":-58.5375043613839,"fPixeltoY":-3.29677296454728,"fXlowNDC":0.00999999977648258,"fYlowNDC":0.259999999776483,"fXUpNDC":0.990000000223517,"fYUpNDC":0.490000000223517,"fWNDC":0.980000000447035,"fHNDC":0.230000000447035,"fAbsXlowNDC":0.00999999977648258,"fAbsYlowNDC":0.259999999776483,"fAbsWNDC":0.980000000447035,"fAbsHNDC":0.230000000447035,"fUxmin":0,"fUymin":0,"fUxmax":2,"fUymax":468.3,"fTheta":30,"fPhi":30,"fAspectRatio":0,"fNumber":3,"fTickx":0,"fTicky":0,"fLogx":0,"fLogy":0,"fLogz":0,"fPadPaint":0,"fCrosshair":0,"fCrosshairPos":0,"fBorderSize":2,"fBorderMode":0,"fModified":false,"fGridx":false,"fGridy":false,"fAbsCoord":false,"fEditable":true,"fFixedAspectRatio":false,"fPrimitives":{"_typename":"TList","name":"TList","arr":[{"_typename":"TFrame","fUniqueID":0,"fBits":8,"fLineColor":1,"fLineStyle":1,"fLineWidth":1,"fFillColor":0,"fFillStyle":1001,"fX1":0,"fY1":0,"fX2":2,"fY2":468.3,"fBorderSize":1,"fBorderMode":0},{"_typename":"TH1D","fUniqueID":0,"fBits":521,"fName":"ft_zq_Pt_nTpc[2]_copy","fTitle":"ft_zq_Pt_nTpc[2]","fLineColor":1,"fLineStyle":1,"fLineWidth":1,"fFillColor":0,"fFillStyle":1001,"fMarkerColor":1,"fMarkerStyle":8,"fMarkerSize":1,"fNcells":102,"fXaxis":{"_typename":"TAxis","fUniqueID":0,"fBits":0,"fName":"xaxis","fTitle":"","fNdivisions":510,"fAxisColor":1,"fLabelColor":1,"fLabelFont":42,"fLabelOffset":0.005,"fLabelSize":0.035,"fTickLength":0.03,"fTitleOffset":1,"fTitleSize":0.035,"fTitleColor":1,"fTitleFont":42,"fNbins":100,"fXmin":0,"fXmax":2,"fXbins":[],"fFirst":0,"fLast":0,"fBits2":0,"fTimeDisplay":false,"fTimeFormat":"","fLabels":null,"fModLabs":null},"fYaxis":{"_typename":"TAxis","fUniqueID":0,"fBits":0,"fName":"yaxis","fTitle":"","fNdivisions":510,"fAxisColor":1,"fLabelColor":1,"fLabelFont":42,"fLabelOffset":0.005,"fLabelSize":0.035,"fTickLength":0.03,"fTitleOffset":1,"fTitleSize":0.035,"fTitleColor":1,"fTitleFont":42,"fNbins":1,"fXmin":0,"fXmax":1,"fXbins":[],"fFirst":0,"fLast":0,"fBits2":0,"fTimeDisplay":false,"fTimeFormat":"","fLabels":null,"fModLabs":null},"fZaxis":{"_typename":"TAxis","fUniqueID":0,"fBits":0,"fName":"zaxis","fTitle":"","fNdivisions":510,"fAxisColor":1,"fLabelColor":1,"fLabelFont":42,"fLabelOffset":0.005,"fLabelSize":0.035,"fTickLength":0.03,"fTitleOffset":1,"fTitleSize":0.035,"fTitleColor":1,"fTitleFont":42,"fNbins":1,"fXmin":0,"fXmax":1,"fXbins":[],"fFirst":0,"fLast":0,"fBits2":0,"fTimeDisplay":false,"fTimeFormat":"","fLabels":null,"fModLabs":null},"fBarOffset":0,"fBarWidth":1000,"fEntries":10300,"fTsumw":10300,"fTsumw2":10300,"fTsumwx":5678.98,"fTsumwx2":5044.6372,"fMaximum":-1111,"fMinimum":-1111,"fNormFactor":0,"fContour":[],"fSumw2":[],"fOption":"","fFunctions":{"_typename":"TList","name":"TList","arr":[],"opt":[]},"fBufferSize":0,"fBuffer":[],"fBinStatErrOpt":0,"fStatOverflows":2,"fArray":[0,180,431,446,309,220,176,192,152,162,201,175,200,193,202,206,229,250,212,207,188,195,210,162,186,183,163,194,164,168,171,204,155,165,152,135,140,137,126,148,112,114,98,102,114,99,91,83,68,79,72,64,73,79,68,56,57,72,53,51,48,48,50,42,38,34,37,48,36,24,36,30,40,34,38,16,15,21,22,33,27,26,15,18,18,20,13,19,14,18,14,17,11,16,12,11,9,7,13,10,8,290]}],"opt":["",""]},"fExecs":{"_typename":"TList","name":"TList","arr":[],"opt":[]},"fName":"c_sg_3","fTitle":"c_sg_3","fNumPaletteColor":0,"fNextPaletteColor":0},{"_typename":"TPad","fUniqueID":0,"fBits":9,"fLineColor":1,"fLineStyle":1,"fLineWidth":1,"fFillColor":0,"fFillStyle":1001,"fLeftMargin":0.1,"fRightMargin":0.1,"fBottomMargin":0.1,"fTopMargin":0.1,"fXfile":2,"fYfile":2,"fAfile":1,"fXstat":0.99,"fYstat":0.99,"fAstat":2,"fFrameFillColor":0,"fFrameLineColor":1,"fFrameFillStyle":1001,"fFrameLineStyle":1,"fFrameLineWidth":1,"fFrameBorderSize":1,"fFrameBorderMode":0,"fX1":-0.250000018626453,"fY1":-42.7875031879174,"fX2":2.25000001862645,"fY2":385.087503187917,"fXtoAbsPixelk":42.7680522423268,"fXtoPixelk":38.8080523308397,"fXtoPixel":155.231997757673,"fYtoAbsPixelk":746.524049079704,"fYtoPixelk":159.80404925226,"fYtoPixel":-0.414981005432102,"fUtoAbsPixelk":3.9600499114871,"fUtoPixelk":5e-5,"fUtoPixel":388.080000177026,"fVtoAbsPixelk":764.280050172555,"fVtoPixelk":177.560000345111,"fVtoPixel":-177.560000345111,"fAbsPixeltoXk":-0.275510222506383,"fPixeltoXk":-0.250000018626453,"fPixeltoX":0.00644197082073931,"fAbsPixeltoYk":1798.93534717904,"fPixeltoYk":-42.7875031879174,"fPixeltoY":-2.40974884852559,"fXlowNDC":0.00999999977648258,"fYlowNDC":0.00999999977648258,"fXUpNDC":0.990000000223517,"fYUpNDC":0.240000000223517,"fWNDC":0.980000000447035,"fHNDC":0.230000000447035,"fAbsXlowNDC":0.00999999977648258,"fAbsYlowNDC":0.00999999977648258,"fAbsWNDC":0.980000000447035,"fAbsHNDC":0.230000000447035,"fUxmin":0,"fUymin":0,"fUxmax":2,"fUymax":342.3,"fTheta":30,"fPhi":30,"fAspectRatio":0,"fNumber":4,"fTickx":0,"fTicky":0,"fLogx":0,"fLogy":0,"fLogz":0,"fPadPaint":0,"fCrosshair":0,"fCrosshairPos":0,"fBorderSize":2,"fBorderMode":0,"fModified":false,"fGridx":false,"fGridy":false,"fAbsCoord":false,"fEditable":true,"fFixedAspectRatio":false,"fPrimitives":{"_typename":"TList","name":"TList","arr":[{"_typename":"TFrame","fUniqueID":0,"fBits":8,"fLineColor":1,"fLineStyle":1,"fLineWidth":1,"fFillColor":0,"fFillStyle":1001,"fX1":0,"fY1":0,"fX2":2,"fY2":342.3,"fBorderSize":1,"fBorderMode":0},{"_typename":"TH1D","fUniqueID":0,"fBits":521,"fName":"ft_zq_Pt_nTpc[3]_copy","fTitle":"ft_zq_Pt_nTpc[3]","fLineColor":1,"fLineStyle":1,"fLineWidth":1,"fFillColor":0,"fFillStyle":1001,"fMarkerColor":1,"fMarkerStyle":8,"fMarkerSize":1,"fNcells":102,"fXaxis":{"_typename":"TAxis","fUniqueID":0,"fBits":0,"fName":"xaxis","fTitle":"","fNdivisions":510,"fAxisColor":1,"fLabelColor":1,"fLabelFont":42,"fLabelOffset":0.005,"fLabelSize":0.035,"fTickLength":0.03,"fTitleOffset":1,"fTitleSize":0.035,"fTitleColor":1,"fTitleFont":42,"fNbins":100,"fXmin":0,"fXmax":2,"fXbins":[],"fFirst":0,"fLast":0,"fBits2":0,"fTimeDisplay":false,"fTimeFormat":"","fLabels":null,"fModLabs":null},"fYaxis":{"_typename":"TAxis","fUniqueID":0,"fBits":0,"fName":"yaxis","fTitle":"","fNdivisions":510,"fAxisColor":1,"fLabelColor":1,"fLabelFont":42,"fLabelOffset":0.005,"fLabelSize":0.035,"fTickLength":0.03,"fTitleOffset":1,"fTitleSize":0.035,"fTitleColor":1,"fTitleFont":42,"fNbins":1,"fXmin":0,"fXmax":1,"fXbins":[],"fFirst":0,"fLast":0,"fBits2":0,"fTimeDisplay":false,"fTimeFormat":"","fLabels":null,"fModLabs":null},"fZaxis":{"_typename":"TAxis","fUniqueID":0,"fBits":0,"fName":"zaxis","fTitle":"","fNdivisions":510,"fAxisColor":1,"fLabelColor":1,"fLabelFont":42,"fLabelOffset":0.005,"fLabelSize":0.035,"fTickLength":0.03,"fTitleOffset":1,"fTitleSize":0.035,"fTitleColor":1,"fTitleFont":42,"fNbins":1,"fXmin":0,"fXmax":1,"fXbins":[],"fFirst":0,"fLast":0,"fBits2":0,"fTimeDisplay":false,"fTimeFormat":"","fLabels":null,"fModLabs":null},"fBarOffset":0,"fBarWidth":1000,"fEntries":6836,"fTsumw":6836,"fTsumw2":6836,"fTsumwx":3749.16,"fTsumwx2":3335.9324,"fMaximum":-1111,"fMinimum":-1111,"fNormFactor":0,"fContour":[],"fSumw2":[],"fOption":"","fFunctions":{"_typename":"TList","name":"TList","arr":[],"opt":[]},"fBufferSize":0,"fBuffer":[],"fBinStatErrOpt":0,"fStatOverflows":2,"fArray":[0,131,306,326,219,134,120,120,98,109,127,105,128,124,133,139,151,172,149,121,119,125,130,103,124,119,101,125,108,113,119,141,101,114,105,91,87,90,77,99,77,78,61,58,72,65,67,54,44,56,54,39,54,59,50,33,35,47,31,34,33,29,33,24,29,20,23,35,24,12,27,20,27,28,27,12,10,11,17,19,20,14,8,12,13,13,6,13,9,14,6,13,6,11,8,7,7,6,8,5,6,200]}],"opt":["",""]},"fExecs":{"_typename":"TList","name":"TList","arr":[],"opt":[]},"fName":"c_sg_4","fTitle":"c_sg_4","fNumPaletteColor":0,"fNextPaletteColor":0},{"_typename":"TStyle","fUniqueID":0,"fBits":0,"fName":"Modern","fTitle":"Modern Style","fLineColor":1,"fLineStyle":1,"fLineWidth":1,"fFillColor":19,"fFillStyle":1001,"fMarkerColor":1,"fMarkerStyle":8,"fMarkerSize":1,"fTextAngle":0,"fTextSize":0.05,"fTextAlign":11,"fTextColor":1,"fTextFont":62,"fXaxis":{"_typename":"TAttAxis","fNdivisions":510,"fAxisColor":1,"fLabelColor":1,"fLabelFont":42,"fLabelOffset":0.005,"fLabelSize":0.035,"fTickLength":0.03,"fTitleOffset":1,"fTitleSize":0.035,"fTitleColor":1,"fTitleFont":42},"fYaxis":{"_typename":"TAttAxis","fNdivisions":510,"fAxisColor":1,"fLabelColor":1,"fLabelFont":42,"fLabelOffset":0.005,"fLabelSize":0.035,"fTickLength":0.03,"fTitleOffset":1,"fTitleSize":0.035,"fTitleColor":1,"fTitleFont":42},"fZaxis":{"_typename":"TAttAxis","fNdivisions":510,"fAxisColor":1,"fLabelColor":1,"fLabelFont":42,"fLabelOffset":0.005,"fLabelSize":0.035,"fTickLength":0.03,"fTitleOffset":1,"fTitleSize":0.035,"fTitleColor":1,"fTitleFont":42},"fBarWidth":1,"fBarOffset":0,"fColorModelPS":0,"fDrawBorder":0,"fOptLogx":0,"fOptLogy":0,"fOptLogz":0,"fOptDate":0,"fOptStat":221112211,"fOptTitle":0,"fOptFile":0,"fOptFit":1,"fShowEventStatus":0,"fShowEditor":0,"fShowToolBar":0,"fNumberContours":20,"fAttDate":{"_typename":"TAttText","fTextAngle":0,"fTextSize":0.025,"fTextAlign":11,"fTextColor":1,"fTextFont":62},"fDateX":0.01,"fDateY":0.01,"fEndErrorSize":2,"fErrorX":0.5,"fFuncColor":2,"fFuncStyle":1,"fFuncWidth":2,"fGridColor":0,"fGridStyle":3,"fGridWidth":1,"fLegendBorderSize":1,"fLegendFillColor":0,"fLegendFont":42,"fLegendTextSize":0,"fHatchesLineWidth":1,"fHatchesSpacing":1,"fFrameFillColor":0,"fFrameLineColor":1,"fFrameFillStyle":1001,"fFrameLineStyle":1,"fFrameLineWidth":1,"fFrameBorderSize":1,"fFrameBorderMode":0,"fHistFillColor":0,"fHistLineColor":1,"fHistFillStyle":1001,"fHistLineStyle":1,"fHistLineWidth":3,"fHistMinimumZero":false,"fHistTopMargin":0.05,"fCanvasPreferGL":false,"fCanvasColor":0,"fCanvasBorderSize":2,"fCanvasBorderMode":0,"fCanvasDefH":500,"fCanvasDefW":700,"fCanvasDefX":10,"fCanvasDefY":10,"fPadColor":0,"fPadBorderSize":2,"fPadBorderMode":0,"fPadBottomMargin":0.1,"fPadTopMargin":0.1,"fPadLeftMargin":0.1,"fPadRightMargin":0.1,"fPadGridX":false,"fPadGridY":false,"fPadTickX":0,"fPadTickY":0,"fPaperSizeX":20,"fPaperSizeY":26,"fScreenFactor":1,"fStatColor":0,"fStatTextColor":1,"fStatBorderSize":1,"fStatFont":42,"fStatFontSize":0,"fStatStyle":1001,"fStatFormat":"6.4g","fStatX":0.98,"fStatY":0.935,"fStatW":0.2,"fStatH":0.16,"fStripDecimals":true,"fTitleAlign":23,"fTitleColor":0,"fTitleTextColor":1,"fTitleBorderSize":0,"fTitleFont":42,"fTitleFontSize":0.05,"fTitleStyle":0,"fTitleX":0.5,"fTitleY":0.995,"fTitleW":0,"fTitleH":0,"fLegoInnerR":0.5,"fLineStyle":["","  "," 12 12"," 4 8"," 12 16 4 16"," 20 12 4 12"," 20 12 4 12 4 12 4 12"," 20 20"," 20 12 4 12 4 12"," 80 20"," 80 40 4 40","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "],"fHeaderPS":"","fTitlePS":"","fFitFormat":"5.4g","fPaintTextFormat":"g","fLineScalePS":3,"fJoinLinePS":0,"fCapLinePS":0,"fTimeOffset":788918400,"fImageScaling":1}],"opt":["","","","",""]},"fExecs":null,"fName":"c_sg","fTitle":"Signal gain level","fNumPaletteColor":0,"fNextPaletteColor":0,"fDISPLAY":"$DISPLAY","fDoubleBuffer":0,"fRetained":true,"fXsizeUser":0,"fYsizeUser":0,"fXsizeReal":10,"fYsizeReal":20,"fWindowTopX":0,"fWindowTopY":0,"fWindowWidth":0,"fWindowHeight":0,"fCw":396,"fCh":772,"fCatt":{"_typename":"TAttCanvas","fXBetween":2,"fYBetween":2,"fTitleFromTop":1.2,"fXdate":0.2,"fYdate":0.3,"fAdate":1},"kMoveOpaque":true,"kResizeOpaque":true,"fHighLightColor":2,"fBatch":true,"kShowEventStatus":false,"kAutoExec":true,"kMenuBar":true});
            Core.key_handling = false;
            Core.draw("root_plot_1617292798985", obj, "");
        }
    );
}
</script>



Now we can try to estimate what influence has [incorrectness triggering](#False-triggering)


    Canvas(toolbar=Toolbar(toolitems=[('Home', 'Reset original view', 'home', 'home'), ('Back', 'Back to previous …





    
![svg](4TracksAnalysis_files/4TracksAnalysis_13_1.svg)
    






    772



Now  let's try to see what tracks we lost from signal area and what contribution they have:

TPC and ITS has different coverage for polar angle:

![img1](https://camo.githubusercontent.com/9a7ab40d0f74a866a7095986644134a0f72cc58b/68747470733a2f2f70702e757365726170692e636f6d2f633835323231362f763835323231363738332f3131396137332f304f76685f6c544b4e7a552e6a7067)

Perhaps we have tracks that not only can't reach TPC, but also has $\theta$ values that TPC doesn't cover.

Below we can see polar angle distribution for tracks that covers three cases:

1. All tracks from events were reconstructed by ITS and TPC
2. Only ITS tracks from events with only part TPC tracks. Here tracks that not reconstructed by TPC
3. All tracks from events were reconstructed by ITS or TPC

We can see small gaps with for the second case, that allow to speak about correctness of the suggestion, but anyway low energy of tracks is the main reason why TPC can't reconstructed tracks.  


    ---------------------------------------------------------------------------

    NameError                                 Traceback (most recent call last)

    <ipython-input-18-4feb77cac62d> in <module>
    ----> 1 ShowComparison('$\\theta$',[AllTPCTracksTheta, ITSDiffTPCTracksTheta, TotalLowPtTheta], '$^\\circ$', ['ITS&&TPC', 'OnlyITSFromNTPCEvents', 'ITS||TPC'], None, nBins=80, ranges=(25,150))
    

    NameError: name 'ShowComparison' is not defined


## Mass
Let's see on the mass distribution of the events



    Canvas(toolbar=Toolbar(toolitems=[('Home', 'Reset original view', 'home', 'home'), ('Back', 'Back to previous …





    
![svg](4TracksAnalysis_files/4TracksAnalysis_19_1.svg)
    



Let's compare masses of events with handle triggering manipulations:

_see False triggering chapter below_


    Canvas(toolbar=Toolbar(toolitems=[('Home', 'Reset original view', 'home', 'home'), ('Back', 'Back to previous …





    
![svg](4TracksAnalysis_files/4TracksAnalysis_21_1.svg)
    



Let's normalize this plot:


    Canvas(toolbar=Toolbar(toolitems=[('Home', 'Reset original view', 'home', 'home'), ('Back', 'Back to previous …





    
![svg](4TracksAnalysis_files/4TracksAnalysis_23_1.svg)
    



+### Pions subsystems

In our process 4 pions were producted. The most probably intermediate state including two pions and $\rho$ i.e.
$$\rho' \rightarrow \rho \ \pi^+ \pi^- \rightarrow \pi^+ \pi^- \pi^+ \pi^-$$ 

We can see this on distribution of mass that can be obtained as all combinations of pairs from intial four tracks, i.e. only four pairs:

![img](https://camo.githubusercontent.com/53a52e2a6d4ae7112d74f4073c979a51166170d8/68747470733a2f2f70702e757365726170692e636f6d2f633835333632342f763835333632343436372f34383466332f5431375a754b597062526f2e6a7067)

Here we can plot two distirbutions:

1. Make all possible(4) combinations of pairs. Then take lightest and pair that belong to one combination with that. Plot masses of these two pairs.
2. Plot masses of masses from possible combinations.


    Canvas(toolbar=Toolbar(toolitems=[('Home', 'Reset original view', 'home', 'home'), ('Back', 'Back to previous …


    No handles with labels found to put in legend.
    findfont: Font family ['TeX Gyre Heros'] not found. Falling back to DejaVu Sans.
    findfont: Font family ['TeX Gyre Heros'] not found. Falling back to DejaVu Sans.
    findfont: Font family ['TeX Gyre Heros'] not found. Falling back to DejaVu Sans.
    




    
![svg](4TracksAnalysis_files/4TracksAnalysis_25_2.svg)
    



As we can see above, for second case (all possible pairs) we've got stronger signal in comparison with light-recoil pair as it made in [STAR work](http://arxiv.org/abs/0912.0604v2). Let's build 2d distirbuition and marginals component separately:


    Canvas(toolbar=Toolbar(toolitems=[('Home', 'Reset original view', 'home', 'home'), ('Back', 'Back to previous …


    No handles with labels found to put in legend.
    




    
![svg](4TracksAnalysis_files/4TracksAnalysis_27_2.svg)
    



## Cross section

Let's see to cross section of my events.

For this we should take luminosity of runs.

> Unfortunately file that I have to use for getting luminosity have a reference to special class AliTriggerInfo and moreover it packed into TObjArray, so I can't read it via uproot4. This is the reason why I used pure root again. [Here is the script](https://github.com/bdrum/cern-physics/blob/master/root-cpp/RhoPrime/macro/lumi.C) that I used.

Then let's see how much events do we have in each run.

$$L = \frac{1}{\sigma} \frac{\delta N}{\delta t}$$, this means that 

$$\sigma \approx \frac{N}{L}$$

Cross section of phenomena should be flat and independent from runs. 

Let's check it:




    count    119.000000
    mean       5.611438
    std        1.558305
    min        1.621205
    25%        4.630173
    50%        5.584997
    75%        6.479376
    max       10.036004
    Name: sigma, dtype: float64




    Canvas(toolbar=Toolbar(toolitems=[('Home', 'Reset original view', 'home', 'home'), ('Back', 'Back to previous …





    
![svg](4TracksAnalysis_files/4TracksAnalysis_30_1.svg)
    



## Other decays

In PDG I've seen also other interesting modes for $\rho'$:

- 1. $\rho' \rightarrow \eta_0 \rho_0$ | ?
   - 1.1. $\rho_0 \rightarrow 4 \pi$ | $2*10^{-5}\%$
   - 1.2. $\rho_0 \rightarrow \pi^+ \pi^-$ | $10^{-2}\%$
   - 1.3. $\eta_0' \rightarrow  \pi^+ \pi^- \gamma$ | $4\%$
   - 1.4. $\eta_0' \rightarrow  \pi^+ \pi^- \pi^0$ | $23\%$
- 2. $\rho' \rightarrow 4 \pi$ | ?

What about $\rho' \rightarrow \rho_0 \rho_0$ is it possible?

## Decay angle for $\rho_0$

According to [65](https://arxiv.org/pdf/1903.00166.pdf) 

$$cos \theta = \frac{2E_{\pi}}{E_{\rho}-1} 1/ \sqrt{1 - 4\frac{m_{\pi}^2}{m_{\rho}^2}}$$

$$E_{\pi}=\sqrt{m_{\pi}^2+p_{\pi}^2}$$
$$E_{\rho}=\sqrt{m_{\rho}^2+p_{\rho}^2}$$

Very close result from [Landau T2 par.11 exc.2](file:///D:/GoogleDrive/Books/phys/%D0%9B%D0%B0%D0%BD%D0%B4%D0%B0%D1%83,%20%D0%9B%D0%B8%D1%84%D1%88%D0%B8%D1%86%20-%20%D0%A2%D0%B5%D0%BE%D1%80.%20%D1%84%D0%B8%D0%B7%D0%B8%D0%BA%D0%B0/%D0%9B%D0%B0%D0%BD%D0%B4%D0%B0%D1%83%20%D0%9B.%D0%94.,%20%D0%9B%D0%B8%D1%84%D1%88%D0%B8%D1%86%20%D0%95.%D0%9C.%20-%20%D0%A2%D0%B5%D0%BE%D1%80%D0%B5%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B0%D1%8F%20%D1%84%D0%B8%D0%B7%D0%B8%D0%BA%D0%B0.%20%D0%A2%D0%BE%D0%BC%2002%20%D0%B8%D0%B7%2010.%20%D0%A2%D0%B5%D0%BE%D1%80%D0%B8%D1%8F%20%D0%BF%D0%BE%D0%BB%D1%8F%20(2003.8.%D0%B8%D0%B7%D0%B4)(T).pdf)

$$\cos \theta = \frac{\sqrt{E^2-|P|E}-M_\rho/2}{\sqrt{M_\rho^2-4m_\pi^2}|P|/E}$$




    entry
    20        0.432236
    42        0.630956
    96        0.782677
    198       1.014306
    200       0.670207
                ...   
    106367    1.163941
    106383    1.260068
    106461    0.911308
    106497    0.889234
    106687    0.899221
    Name: Recoil, Length: 3008, dtype: float32



## $ \downarrow \downarrow \downarrow \downarrow$ DEBUG $ \downarrow \downarrow \downarrow \downarrow$


## $\uparrow$$\uparrow$$\uparrow$$\uparrow$ DEBUG $\uparrow$$\uparrow$$\uparrow$$\uparrow$

