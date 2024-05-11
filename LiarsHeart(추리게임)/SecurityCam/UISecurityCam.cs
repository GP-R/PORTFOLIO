using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.UI;

public class UISecurityCam : UIPopup
{
    [SerializeField] private TMP_Text titleText;
    [SerializeField] private Image viewportImage;

    [SerializeField] private ToggleGroup dateToggles;
    [SerializeField] private ToggleGroup timeToggles;

    [SerializeField] private Transform dateArea;
    [SerializeField] private Transform timeArea;

    [SerializeField] private GameObject signalButton;
    [SerializeField] private GameObject noSignalButton;

    [SerializeField] private List<UISecurityCamButton> dateButtons = new List<UISecurityCamButton>();
    [SerializeField] private List<UISecurityCamButton> timeButtons = new List<UISecurityCamButton>();

    [SerializeField] private Button closeButton;

    // Listening
    [SerializeField] private SecurityCamEventChannelSO setSecurityCamEvent;
    [SerializeField] private ImageByTimesEventChannelSO setImageByTimeEvent;

    // Broadcasting
    [SerializeField] private StringEventChannelSO onClickDateButtonEvent;

    const string path = "Events/SecurityCam/";

    private void Awake()
    {
        setSecurityCamEvent = Resources.Load<SecurityCamEventChannelSO>(path + "SetSecurityCamEvent");
        setImageByTimeEvent = Resources.Load<ImageByTimesEventChannelSO>(path + "SetImageByTimeEvent");
        onClickDateButtonEvent = Resources.Load<StringEventChannelSO>(path + "OnClickDateButtonEvent");
    }

    private void OnEnable()
    {
        setSecurityCamEvent.OnEventRaised += CreateDateButton;
        setImageByTimeEvent.OnEventRaised += CreateTimeButton;
        closeButton.onClick.AddListener(CloseUI);
    }

    private void OnDisable()
    {
        setSecurityCamEvent.OnEventRaised -= CreateDateButton;
        setImageByTimeEvent.OnEventRaised -= CreateTimeButton;
        closeButton.onClick.RemoveListener(CloseUI);
    }

    public void CreateDateButton(SecurityCamSO securityCam)
    {
        ClearButtonList(dateButtons);

        foreach (DateBySecurityCam data in securityCam.DateBySecurityCams)
        {
            UISecurityCamButton bnt = Instantiate(signalButton, dateArea).GetComponent<UISecurityCamButton>();
            bnt.Init(data.Date, dateToggles);
            bnt.EventHandler.AddUIEvent((PointerEventData) => onClickDateButtonEvent.RaiseEvent(data.Date), EUIEventType.Click);
            bnt.EventHandler.AddUIEvent((PointerEventData) => ChangeButtonColor(dateButtons, bnt), EUIEventType.Click);
            dateButtons.Add(bnt);
        }

        CreateNoSignalButton(dateButtons, dateArea, 2);
    }

    public void CreateTimeButton(List<ImageByTime> imageByTimes)
    {
        ClearButtonList(timeButtons);
        viewportImage.sprite = null;

        foreach (ImageByTime data in imageByTimes)
        {
            UISecurityCamButton bnt = Instantiate(signalButton, timeArea).GetComponent<UISecurityCamButton>();
            bnt.Init(data.Time, timeToggles);
            bnt.EventHandler.AddUIEvent((PointerEventData) => SetViewportImage(data.SpriteImage), EUIEventType.Click);
            bnt.EventHandler.AddUIEvent((PointerEventData) => ChangeButtonColor(timeButtons, bnt), EUIEventType.Click);
            timeButtons.Add(bnt);
        }

        CreateNoSignalButton(timeButtons, timeArea, 2);
    }

    private void SetViewportImage(Sprite sprite)
    {
        viewportImage.sprite = sprite;
    }

    private void ChangeButtonColor(List<UISecurityCamButton> buttons, UISecurityCamButton selectedButton)
    {
        ColorBlock tempColor = selectedButton.GetComponent<Toggle>().colors;
        tempColor.normalColor = new Color(0.0f, 0.0f, 0.0f, 0.0f);
        foreach (UISecurityCamButton button in buttons)
        {
            button.GetComponent<Toggle>().colors = tempColor;
        }

        tempColor.normalColor = selectedButton.GetComponent<Toggle>().colors.highlightedColor;
        tempColor.selectedColor = selectedButton.GetComponent<Toggle>().colors.highlightedColor;
        selectedButton.GetComponent<Toggle>().colors = tempColor;
    }

    private void ClearButtonList(List<UISecurityCamButton> buttons)
    {
        foreach (UISecurityCamButton button in buttons)
        {
            Destroy(button.gameObject);
        }
        buttons.Clear();
    }

    private void CreateNoSignalButton(List<UISecurityCamButton> buttons, Transform parent, int count)
    {
        for(int i = 0; i < count; ++i)
        {
            UISecurityCamButton bnt = Instantiate(noSignalButton, parent).GetComponent<UISecurityCamButton>();
            buttons.Add(bnt);
        }
    }

    private void CloseUI()
    {
        ClearButtonList(dateButtons);
        ClearButtonList(timeButtons);
        viewportImage.sprite = null;
        SetVisible(false);
    }
}
