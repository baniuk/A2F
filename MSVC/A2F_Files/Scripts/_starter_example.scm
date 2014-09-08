;; Load main project file - full path must be provided
;; possible problem - file name must be without spaces and always with full patch, use / switch for directories
;; delete previous
(ti-menu-load-string "!del F:\Dropbox\Shares\A2F\Fluent\_name_anod_off.prof")
(ti-menu-load-string "!del F:\Dropbox\Shares\A2F\Fluent\_name_exhaust.prof")
;; load project
(ti-menu-load-string "file/read-case-data F:\Dropbox\Shares\A2F\Fluent\test_MEA_collectors_Ci_on_collectors_0-495V_converged.cas")

;; Na podstawie 4 strumienie BZ.apwz 

;; Setting REFOR input
;; https://www.evernote.com/shard/s97/nl/10730651/73c5396c-29d8-44d2-b3b2-59eb026137c8
;; Aspen settings:
;; T = 700 C							-> 973.15 K (pozycja 7)
;; P = 1.01325 bar						-> not used
;; Nmol_H = 0.008555393 kmol/hr	*1000/3600	-> 0.0023765 mol/s				M_H = 1.007940 g/mol		Nkg_H = Nmol_H * M_H / 1000 = 2.3954e-06 kg/s
;; Nmol_H20 = 0.000166075 kmol/hr			-> 4.61319e-005 mol/s			M_H2O = 18.01528 g/mol		Nkg_H2O = 8.3108e-07 kg/s
;; Nmol_CO = 0.00637393 kmol/hr				-> 0.00177054 mol/s				M_CO = 28.0101 g/mol		Nkg_CO = 4.9593e-05 kg/s
;; Nmol_CO2 = 0.000166075 kmol/hr			-> 4.61319e-005 mol/s			M_CO2 = 44.0095 g/mol		Nkg_CO2 = 2.0302e-06 kg/s
;; Nmol_N2 = 0.0129353 kmol/hr				-> 0.00359314 mol/s				M_N2 = 28.01340 g/mol		Nkg_N2 = 1.0066e-04 kg/s

;; Strumieñ masowy ca³kowity - suma strumieni masowych zwi¹zków (pozycja 5)
;; Ncalk = Nkg_H+Nkg_H2O+Nkg_CO+Nkg_CO2+Nkg_N2 = 1.5551e-04 kg/s
;; Mass fractions:
;; H20 = 0 (pozycja 14)
;; O2 = 0 (pozycja 16)
;; H = Nkg_H/Ncalk = 2.3954e-06/1.5551e-04 = 0.0154 (pozycja 18)
																						5     		  7                    	   14   16   18 
(ti-menu-load-string "define/boundary-conditions/mass-flow-inlet anode-inlet yes yes no 1.5551e-04 no 973.15 no 0 no yes no no 0 no 0 no 0.0154 yes no 0")

;; setting 1 input
;; http://www.evernote.com/shard/s97/sh/73c5396c-29d8-44d2-b3b2-59eb026137c8/39640cfc27aff79bb69c77b9b9644125
;; Aspen settings:
;; T = 680.468 C						-> 953.618 K (pozycja 7)
;; P = 1.01325 bar						-> not used
;; Nmol_H20 = 0.00872 kmol/hr			-> 0.0024 mol/s			M_H2O = 18.01528 g/mol		Nkg_H2O = 4.3237e-05 kg/s
;; Nmol_CO2 = 0.00654 kmol/hr			-> 0.0018 mol/s			M_CO2 = 44.0095 g/mol		Nkg_CO2 = 7.9217e-05 kg/s
;; Nmol_O2 = 0.0742074 kmol/hr			-> 0.0206 mol/s			M_O2 = 31.99880 g/mol		Nkg_O2 = 6.5918e-04 kg/s
;; Nmol_N2 = 0.308688 kmol/hr			-> 0.0857 mol/s			M_N2 = 28.01340 g/mol		Nkg_N2 = 0.0024 kg/s

;; Strumieñ masowy ca³kowity - suma strumieni masowych zwi¹zków (pozycja 5)
;; Ncalk = Nkg_H2O+Nkg_CO2+Nkg_O2+Nkg_N2 = 0.0032 kg/s
;; Mass fractions:
;; H20 = 0 (pozycja 14)
;; O2 = Nkg_O2/Ncalk = 6.5918e-04/0.0032 = 0.2060 (pozycja 16)
;; H = 0 (pozycja 18)
																						  5     	7                         14   16   	 18 
(ti-menu-load-string "define/boundary-conditions/mass-flow-inlet cathode-inlet yes yes no 0.0032 no 953.618 no 0 no yes no no 0 no 0.2060 no 0 yes no 0")
;; -----------------------------------------------------------------
;; (ti-menu-load-string "solve/iterate 1")
;; -----------------------------------------------------------------
;; setting ANOD-OFF output
;; https://www.evernote.com/shard/s97/nl/10730651/73c5396c-29d8-44d2-b3b2-59eb026137c8
;; Pressure as in REFOR
;; composition
;; We must know names of components in stream in Fluent

(ti-menu-load-string "file/write-profile F:/Dropbox/Shares/A2F/Fluent/_name_anod_off.prof anode-outlet , h2o o2 h2 n2")

;; setting EXHAUST output
;; https://www.evernote.com/shard/s97/nl/10730651/73c5396c-29d8-44d2-b3b2-59eb026137c8
;; composition
;; We must know names of components in stream in Fluent

(ti-menu-load-string "file/write-profile F:/Dropbox/Shares/A2F/Fluent/_name_exhaust.prof cathode-outlet , h2o o2 h2 n2")

;; -----------------------------------------------------------------
(ti-menu-load-string "/")
;;(ti-menu-load-string "exit yes")
