function filters = design_equalizer_filters(freqs, Fs, filtOrder)
%DESIGN_EQUALIZER_FILTERS Design IIR equalizer filters around the given bands
%   freqs is a list of frequencies around which to center the filters
%   Fs is the sampling rate

% Fs = 44100;
% freqs = [63 160 400 1000 2500 6250 16000];

% A good point to place the half power frequency is the logarithmic average
% of the two frequencies
% exp((log(f1) + log(f2))/2)

% multiply by this to get normalized frequency
normalFactor = 2/Fs;

filters = cell(1, length(freqs));
for i = 1:length(freqs)
    % todo: design low pass filter instead of bandpass for first band
    if i == 1 
        lastFreq = 1;
    else
        lastFreq = freqs(i - 1);
    end
    
    thisFreq = freqs(i);
    
    if i == length(freqs)
        nextFreq = Fs/2;
    else
        nextFreq = freqs(i + 1);
    end
    
    hp1 = exp((log(lastFreq) + log(thisFreq))/2);
    
    hp2 = exp((log(thisFreq) + log(nextFreq))/2);
    
%     filters(i) = designfilt('bandpassiir', ...
%         'FilterOrder', filtOrder, ...
%         'HalfPowerFrequency1', hp1, ...
%         'HalfPowerFrequency2', hp2, ...
%         'SampleRate', Fs);

    % Design the filter
    specs = fdesign.bandpass('N,Fc1,Fc2',... % ,Ast1,Ap,Ast2
        filtOrder, hp1, hp2, Fs); % , lastFreq*normalFactor, 1, nextFreq*normalFactor);
    % Use a Butterworth Filter, Biquad SOS
    filter = window(specs); % design(specs, 'Systemobject', true);
    
    % Quantize the filter
%     filter.Arithmetic = 'fixed';
%     filter.CoeffAutoScale = false;
%     filter.CoeffWordLength = 16;
%     % filter.CoeffFracLength = 15;
%     filter.AccumWordLength = 40;
%     % filter.AccumFracLength = 31;
    
    
    Q15 = numerictype('Signedness', 'Auto', 'WordLength', 16, 'FractionLength', 15);
    Q9_31 = numerictype('Signedness', 'Auto', 'WordLength', 40, 'FractionLength', 31);
    
%     filter.NumeratorCoefficientsDataType = 'Custom';
%     filter.CustomNumeratorCoefficientsDataType = Q15;
%     
%     filter.DenominatorCoefficientsDataType = 'Custom';
%     filter.CustomDenominatorCoefficientsDataType = Q15;
%     
%     filter.ScaleValuesDataType = 'Custom';
%     filter.CustomScaleValuesDataType = Q15;
%     
%     filter.NumeratorAccumulatorDataType = 'Custom';
%     filter.CustomNumeratorAccumulatorDataType = Q9_31;
%     
%     filter.DenominatorAccumulatorDataType = 'Custom';
%     filter.CustomDenominatorAccumulatorDataType = Q9_31;
%     
%     filter.OutputDataType = 'Custom';
%     filter.CustomOutputDataType = Q15;
%     
%     scale(filter, 'l1', 'MaxNumerator', 1, 'Arithmetic', 'Fixed');
    
    filters(i) = {filter};
end



% To view a filter, `fvtool(filter, 512, Fs)`
end

