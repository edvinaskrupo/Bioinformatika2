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
    - TBD
    
6. Interpretation
     - TBD
