using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using UnityEngine.EventSystems;

public class UISelectButton : MonoBehaviour
{
    [SerializeField] private Image buttonImage;
    [SerializeField] private Image clearImage;
    [SerializeField] private Image arrowImage;

    [SerializeField] private Color greenColor;
    [SerializeField] private Color grayColor;
    [SerializeField] private Color blackColor;
    [SerializeField] private Color unSelectableColor;

    [SerializeField] private TMP_Text buttonText;

    private bool isSelectable = true;
    private UIEventHandler eventHandler = default;

    private void Awake()
    {
        eventHandler = Utility.GetOrAddComponent<UIEventHandler>(this.gameObject);
    }

    private void Start()
    {
        eventHandler.AddUIEvent(HoverEnter, EUIEventType.Enter);
        eventHandler.AddUIEvent(HoverExit, EUIEventType.Exit);
    }

    private void HoverEnter(PointerEventData eventData)
    {
        if(!isSelectable)
        {
            return;
        }

        arrowImage.gameObject.SetActive(true);
        buttonImage.color = greenColor;
        buttonText.color = blackColor;
    }

    private void HoverExit(PointerEventData eventData)
    {
        if (!isSelectable)
        {
            return;
        }

        arrowImage.gameObject.SetActive(false);
        buttonImage.color = blackColor;
        buttonText.color = greenColor;
    }

    public void SetButtonText(string text)
    {
        buttonText.text = text;
    }

    public void SetUnSelectable()
    {
        isSelectable = false;
        clearImage.gameObject.SetActive(true);
        buttonImage.color = unSelectableColor;
        buttonText.color = grayColor;
        buttonText.fontStyle = FontStyles.Strikethrough;
    }
}
