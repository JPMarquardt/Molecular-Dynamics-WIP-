%%
%variable entry
data = importdata('/Users/paul/Documents/School/2021-2022 S1/CHEM 483/Lab 2 Week 2-6/Week 3/Week 3 Results/Data final.xlsx');
%you have to import your own data
wavelengths = data.data(:,1);
POSTSDSRED = data.data(:,2);
POSTSDSFLU = data.data(:,3);
POSTSDSFLUFLU = data.data(:,4);
PRESDSRED = data.data(:,5);
PRESDSFLU = data.data(:,6);
PRESDSFLUFLU = data.data(:,7);
POSTCTABRED = data.data(:,8);
POSTCTABFLU = data.data(:,9);
POSTCTABFLUFLU = data.data(:,10);
PRECTABRED = data.data(:,11);
PRECTABFLU = data.data(:,12);
PRECTABFLUFLU = data.data(:,13);
wavelength400 = data.data(62:end,1);

%%
%graph making uv vis
figurer(POSTCTABRED,wavelengths,'CTAB with Methyl Red indicator above its CMC');
figurer(PRECTABRED,wavelengths,'CTAB with Methyl Red indicator below its CMC');
figurer(POSTSDSRED,wavelengths,'SDS with Methyl Red indicator above its CMC');
figurer(PRESDSRED,wavelengths,'SDS with Methyl Red indicator below its CMC');
figurer(POSTCTABFLU,wavelengths,'CTAB with Fluorescein indicator above its CMC');
figurer(PRECTABFLU,wavelengths,'CTAB with Fluorescein indicator below its CMC');
figurer(POSTSDSFLU,wavelengths,'SDS with Fluorescein indicator above its CMC');
figurer(PRESDSFLU,wavelengths,'SDS with Fluorescein indicator below its CMC');
%sorry I am NOT going to go through the data individually taking 10 minutes
%per set to finely adjust the parameters for each equation a simple lab
%report for this class should not take 10 hours if you want me to do that
%hire me for undergrad research NOT a 2 credit lab course

%this function is FINE for the majority of the data and for the one i didnt
%i adjusted the parameters


%%
%graph making fluorescence
figure('name','SDS');
hold on;
plot(wavelengths,POSTSDSFLUFLU,'-','linewidth',2);
plot(wavelengths,PRESDSFLUFLU,'-','linewidth',2);
legend({'Fluoresence spectrum of SDS above the CMC concentrartion','Fluoresence spectrum of SDS below the CMC concentrartion'});
axis([380,600,0,1]);
xlabel('Wavelength (nm)');
ylabel('Fluoresence');
hold off;

figure('name','CTAB');
hold on;
plot(wavelengths,POSTCTABFLUFLU,'-','linewidth',2);
plot(wavelengths,PRECTABFLUFLU,'-','linewidth',2);
legend({'Fluoresence spectrum of CTAB above the CMC concentrartion','Fluoresence spectrum of CTAB below the CMC concentrartion'});
axis([380,600,0,1]);
xlabel('Wavelength (nm)');
ylabel('Fluoresence');
hold off;
%%
%functions
function figuress = figurer(data1,wave,label)
    xvals = 380:4:700;
    ft = fittype('z+a1*exp(-((x-b1)/c1)^2) + a2*exp(-((x-b2)/c2)^2)','indep','x');
    Fit = fit(wave,data1,ft,'lower',[0 0 380 380 0 0 0],'upper',[inf inf 700 700 inf inf 1],'startpoint',[0 0 450 450 0.5 0.5 0])
    figuress = figure('name',label);
    a = plot(wave,data1,'-','linewidth',2,'color','black');
    hold on;
    c = plotter(Fit);
    plot(c(1,:),c(2,:),'-','linewidth',2,'color','#0072BD');
    plot(c(1,:),c(3,:),'-','linewidth',2,'color','#77AC30');
    b = plot(xvals,Fit(xvals),'--','linewidth',2,'color','red');


    legend({label,'Two-term gassuian model of above','First term of the gaussian model','Second term of the gaussian model'});
    axis([380,600,0,0.7]);
    xlabel('Wavelength (nm)');
    ylabel('Absorbance');
    hold off;
end
function plotss = plotter(inputgauss)
    xvals = 380:4:700;
    yval1 = [];
    yval2 = [];
    for i = 1:length(xvals)
        yval1(i) = inputgauss.z+inputgauss.a1*exp(-((xvals(i)-inputgauss.b1)/inputgauss.c1)^2);
        yval2(i) = inputgauss.z+inputgauss.a2*exp(-((xvals(i)-inputgauss.b2)/inputgauss.c2)^2);
    end
    plotss = [xvals; yval1; yval2];
end