# dsp-brazuka-repo-traduz-BR-pro-JUCE_FRAMEWORK
bora traduzir

certo, nao documentada a configuracao para build em ambiente Linux, que e o escopo deste projeto, pois se usas Linux deves saber como se faz, entao bora, percebi que por estudar a lingua Inglesa, as coisas veem fluindo muito bem, e percebi, apos tentar traduzir foruns em linguas distintas para estudos cyber, que traducoes feitas puramente por identificacao de padroes textuais no estilo dados... enfim, sem mais delongas creio que ainda e benefico uma pessoa que traduza manualmente as documentacoes e como eu estou lendo pela primeira vez sera benefico gerar um log das traducoes para los brasilenos.
Obviamente na hora de traduzir tentarei manter mais focado em apenas traduzir de maneira concisa nao apenas para .me, .uuuuutu :) `::`

# EM DOCUMENTACAO OFICIAL [https://docs.juce.com/master/tutorial_code_basic_plugin.html]

# Orientacoes
  Cada projeto recentemente criado de design de plugins, tras consigo duas classes principais, a de processador de plugin (PluginProcessor) que faz o manuseio de operacoes de audio e MIDI I/O, juntamente com processamento de logica (??).Da outra classe que sera a de edicao de plugins (PluginEditor), que fara o manuseio de eventos de tela (on screen GUI) carregando mecanismos de controle ou visualizacoes.
  Quando passadas informacoes entre essas duas classes (PluginProcessor || PluginEditor) consideraremos que a classe PluginProcessor eh a classe mae da classe PluginEditor. Existe apenas um processador de plugin que podemos usar para criar multiplos editores. Cada editor possui uma referencia ao processador tal qual pode editar e/ou acessar informacoes e parametros das threads de audio, e fica de responsabilidade do editor de setar e fazer fetch das informacoes nas threads do processador e nao o contrario.
  A funcao principal que estaremos editando no arquivo PluginProcessor.cpp e o metodo processBlock() que recebera datos de audio e MIDI e trara como output os mesmos para o output do Plugin. 
  A funcao que mudaremos no arquivo PluginEditor.cpp eh o construtor da classe, que ao ser inicializado gerara uma GUI com objetos, bem como o metodo paint() que poderemos desenhar controles extras e customizados de componentes GUI.
  O editor contrutor atualmente possui uma chamada de metodo - setSize(400, 300) - que faz o setup do tamanho das dimensoes GUI (interface grafica) do projeto para esta simples aplicacao.
 
 ###
    TutorialPluginAudioProcessorEditor::TutorialPluginAudioProcessorEditor (TutorialPluginAudioProcessor& p)
      : AudioProcessorEditor (&p), audioProcessor (p)
  {
      // This is where our plugin’s editor size is set.
      setSize (200, 200);
  }
 ###
 
 # Criando um simples controle de interface grafica a.k.a GUI (display de tela)
 criaremos um simples \\slider// que mudara o volume das mensagens MIDI na medida em que os sinais/dados MIDI chegam
  # diagrama de [-linhagem/->[herdou)(de]](inheritance) da classe Slider
    Diagrama indexado:
    diagrama01.png
  # INDEX diagrama:
  [+1+] MouseListener (ponteiro que constantemente escuta por acoes/triggers de controle de mouse a.k.a qualquer movida de mouse ativa, quando componente ativo tambem provavelmente, entao seria tipo:
QUANDO botao mouse esquerdo estiver apertado E o mouse trigger evento que espera movida de mouses for ativado, ou seja, quando .isso e o mouse mecher, o slider meche junto.
No arquivo Header do PluginEditor.h o adicionaremos:::juce::Slider midiVolume; // [1] 
Agora podemos setar as propriedades do knob de slider com varias funcoes no editor do construtor. Devemos tambem chamar addAndMakeVisible (&midiVolume) para que o knob de slider se atrele ao editor GUI (display de tela). Adicione:::// these define the parameters of our slider object
    midiVolume.setSliderStyle (juce::Slider::LinearBarVertical);
    midiVolume.setRange (0.0, 127.0, 1.0);
    midiVolume.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    midiVolume.setPopupDisplayEnabled (true, false, this);
    midiVolume.setTextValueSuffix (" Volume");
    midiVolume.setValue(1.0);
 
    // this function adds the slider to the editor
    addAndMakeVisible (&midiVolume);
    // em PluginEditor.cpp
 
 As janelas JUCE possuem um metodo chamado resized() que se traduz para repaginar, ou em outro portugues, redimensionar, que eh chamado uma vez ao inicializar a janela e toda a vez que a janela eh redimensionada pelo usuario (se habilitado resizing). Podem ser posicionados relativos aos limites da tela.

# Passar informacoes de controle para a classe do processador
  Agora que temos algo controlavel para ajustar, mas que no momento nao controla nada. Preciamos interceptar dados MIDI e reposicionar as notas no volume em nosso slider (??) e isso sera feito no processador. 
  Para que o slider possa controlar os efeitos MIDI na thread do processador precisamos criar uma nova variavel na mesma para que possamos fazer com que o slider altere os valores.
  Para tal, criaremos uma nova variavel publica em:::? chamada noteOnVel (que provavelmente significaria ~nota ligada com envelope de volume (NOTE-On-Volume-EnveLope, por contexto, porem talvez nao seja bem isso~~)
