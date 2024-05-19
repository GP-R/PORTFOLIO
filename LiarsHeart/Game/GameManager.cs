using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : Singleton<GameManager>
{
    public ChapterSO chapter;

    // Managers
    private ResourceManager resource = new ResourceManager();
    public static ResourceManager Resource { get => Instance.resource; }

    private UIManager ui = new UIManager();
    public static UIManager UI { get => Instance.ui; }

    private SoundManager sound = new SoundManager();
    public static SoundManager Sound { get => Instance.sound; }

    private HeartRateManager heartRate = new HeartRateManager();
    public static HeartRateManager HeartRate { get => Instance.heartRate; }

    private SubmitManager submit = new SubmitManager();
    public static SubmitManager Submit { get => Instance.submit; }

    private DialogueManager dialogue = new DialogueManager();
    public static DialogueManager Dialogue { get => Instance.dialogue; }

    private MapManager map = new MapManager();
    public static MapManager Map { get => Instance.map; }

    private CharacterManager character = new CharacterManager();
    public static CharacterManager Character { get => Instance.character; }

    // Scene UI
    UIMainMenu mainMenuUI = default;
    UIHeartRate heartRateUI = default;
    UICharacterPanel characterPanelUI = default;

    protected override void Awake()
    {
        base.Awake();

        //TODO : 임시코드
        if(chapter != null)
        {
            foreach(CharacterSO data in chapter.CharacterData.SuspectCharacteres)
            {
                data.CharacterState = ECharacterState.General;
            }
            Character.Init(chapter.CharacterData);

            Submit.SubmitSO = chapter.SubmitData;
            Map.SetMapData(chapter.MapData);
        }


    }

    void Start()
    {
        // Sound Manger
        Sound.Init();
        Sound.Play("BGM/BGM_MainTheme", ESound.BGM);

        // Main Menu UI Section
        mainMenuUI = UI.LoadSceneUI<UIMainMenu>("MainMenu");
        mainMenuUI.SetVisible(true);

        // Character Panel UI Section
        characterPanelUI = UI.LoadSceneUI<UICharacterPanel>("CharacterPanel");
        characterPanelUI.SetVisible(true);

        // Heart Rate Section
        HeartRate.Init();
        HeartRate.OnHeartRate(this);

        heartRateUI = UI.LoadSceneUI<UIHeartRate>("HeartRate");
        heartRateUI.SetVisible(true);

        // Dialogue Manager
        Dialogue.Init();
    }
}
