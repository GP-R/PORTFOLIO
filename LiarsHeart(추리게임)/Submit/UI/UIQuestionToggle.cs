using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using TMPro;

public class UIQuestionToggle : MonoBehaviour
{
    [SerializeField] private Image hoverImage = default;

    [SerializeField] private int number;
    public int Number { get => number; }

    [SerializeField] private string question;

    private TMP_Text toggleText;
    private UIEventHandler eventHandler = default;

    private Toggle toggle = default;
    public Toggle Toggle { get => toggle; }

    private void Awake()
    {
        eventHandler = Utility.GetOrAddComponent<UIEventHandler>(this.gameObject);
        toggle = Utility.GetOrAddComponent<Toggle>(this.gameObject);
    }

    private void Start()
    {
        eventHandler.AddUIEvent(ToggleHover, EUIEventType.Enter);
        eventHandler.AddUIEvent(ToggleHover, EUIEventType.Exit);

        toggle.onValueChanged.AddListener(ChangeColor);
        if(toggle.isOn)
        {
            ChangeColor(true);
        }
    }

    // Enter & Exit UI Event
    private void ToggleHover(PointerEventData eventData)
    {
        if (hoverImage.gameObject.activeSelf)
        {
            hoverImage.gameObject.SetActive(false);
        }
        else
        {
            hoverImage.gameObject.SetActive(true);
        }
    }

    private void ChangeColor(bool isOn)
    {
        ColorBlock colorBlock = toggle.colors;
        if(isOn)
        {
            colorBlock.normalColor = new Color(1.0f, 1.0f, 1.0f, 1.0f);
            colorBlock.highlightedColor = new Color(1.0f, 1.0f, 1.0f, 1.0f);
            colorBlock.selectedColor = new Color(1.0f, 1.0f, 1.0f, 1.0f);
        }
        else
        {
            colorBlock.normalColor = new Color(1.0f, 1.0f, 1.0f, 0.0f);
            colorBlock.highlightedColor = new Color(1.0f, 1.0f, 1.0f, 0.0f);
            colorBlock.selectedColor = new Color(1.0f, 1.0f, 1.0f, 0.0f);
        }
        toggle.colors = colorBlock;
    }

    private void OnDrawGizmos()
    {
        
        toggleText = GetComponentInChildren<TMP_Text>();
        if (toggleText != null)
        {
            toggleText.text = "(" + number + ")" + " " + question;
        }
    }
}
