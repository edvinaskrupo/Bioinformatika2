# Bioinformatika2
2-asis Bioinformatikos kurso laboratorinis darbas

1. Download nucleotide entry NC_045512 from NCBI and save as fasta.
    - Išsaugotas kaip "NC_045512.fasta"

2. Lets collect related genomes.
    - Atsakymas į e): Pašalinam Covid-19 įrašus, kadangi jie sudaro didžiąją dalį rezultatų, bei paslėpia mažiau žinomus beta-koronavirusus.
    - Genomai išsaugoti "seqdump.fasta" faile.
    - Viršuje - MERS (kupranugario viruso) seka.
    - Po ja - NC_045512 seka.
    - Po ja - visos kitos atsisiųstos beta-koronavirusų sekos.
    - Komentaras daliai j): Radau 5 sekas, išsaugojau jas "seqdump2.fasta" faile.
      
3. Remove redundant sequences
    - Genomai išrikiuoti mažėjimo tvarka "seqdump_sorted" faile.
    - Genomai klasterizuoti "seqdump_cluster" faile.
    - Identifikatoriai įrašyti "representatives.txt" faile.
    - Reprezentatyvūs genomai įrašyti "representatives_sequences.fasta" faile.
    - Naudota komanda identifikatoriams rasti:
```bash
grep '... \*$' seqdump_cluster.fasta | sed -n 's/.*>\(.*\)\.\.\. \*$/\1/p' > representatives.txt
```

4. Protein based analysis
    - Baltymo seka "D3W8N4" įrašyta faile "D3W8N4.fasta"
    - Aligned sequences įrašyti faile "aligned_sequences.fasta"
    - Ištranslate'intos sekos įrašytos faile "translated_sequences.fasta"
    - Išfiltruotos sekos įrašytos faile "filtered_sequences.fasta" (pokyčių nėra, visos sekos ilgesnės nei 800)
    - mafft alignmentas įrašytas faile "aligned_sequences_mafft.fasta"
    - Fasttree medis sugeneruotas faile "phylogenetic_tree.tree"

5. Analysis
    - Python kodas išsaugotas faile "analysis.py"
    - Medis su kupranugario viruso šaknim išsaugotas faile "rooted_tree.tree"
    
6. Interpretation
     - How did the Covid-19 evolve, what path through hosts was taken?
       - Iš medžio panašu, jog prieš užkrečiant žmogų, virusas buvo užkrėtęs šikšnosparnius, pasagnosinius šikšnosparnius (horseshoe bat), prieš tai - skujuotinius (pangolins), dar prieš juos - kupranugarius.
     - Would it be different interpretation if out-group is not used?
       - Ir taip ir ne - vis tiek matome kokie gyvūnai nešiojo koronaviruso pirmtaką, tačiau be atsvaros taško, neaišku kuris gyvūnas po kurio ėjo laikui bėgant.
     - What about Urbani SARS origin?
       - Iš medžio panašu, jog šis virusas ganėtinai seniai atsiskyrė nuo Covid19, tad jis neturėtų būti viruso pirmtakas.
     - Is the Palm Civet origin evident?
       - Mano gautame medyje šios atmainos nėra, negaliu daryti išvadų.
