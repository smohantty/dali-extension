#ifndef DALI_TIZEN_WEB_ENGINE_CHROMIUM_H
#define DALI_TIZEN_WEB_ENGINE_CHROMIUM_H

/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

// EXTERNAL INCLUDES
#include <functional>
#include <dali-toolkit/dali-toolkit.h>
#include <dali/devel-api/adaptor-framework/web-engine-plugin.h>
#include <dali/public-api/images/native-image-interface.h>

#include <tbm_surface.h>
#include <unordered_map>

namespace Dali
{
namespace Plugin
{

class WebViewContainerForDali;

/**
 * @brief The interface class to represent client of corresponding WebView container (WebViewContainerForDali).
 */
class WebViewContainerClient
{

public:

  /**
   * @brief Callback function to be called by WebViewContainer when surface is updated.
   * @param [in] buffer The surface
   */
  virtual void UpdateImage( tbm_surface_h buffer ) = 0;

  /**
   * @brief Callback function to be called by WebViewContainer when page loading is started.
   */
  virtual void LoadStarted() = 0;

  /**
   * @brief Callback function to be called by WebViewContainer when page loading is finished.
   */
  virtual void LoadFinished() = 0;

  /**
   * @brief Callback function to be called by WebViewContainer when an error occurs in page loading.
   * @param [in] url Failing URL for this error
   * @param [in] errorCode The error code
   */
  virtual void LoadError( const char* url, int errorCode ) = 0;

  /**
   * @brief Callback function to be called by WebViewContainer when it gets JavaScript evalution result.
   * @param [in] key An unsigned integer representing the result handler
   * @param [in] result Result string from JavaScript runtime
   * @see Dali::Plugin::TizenWebEngineChromium::EvaluateJavaScript
   */
  virtual void RunJavaScriptEvaluationResultHandler( size_t key, const char* result ) = 0;

  /**
   * @brief Callback function to be called by WebViewContainer when a message handler is called from JavaScript runtime.
   * @param [in] objectName Exposed object name of the message handler
   * @param [in] message Message from JavaScript runtime
   * @see Dali::Plugin::TizenWebEngineChromium::AddJavaScriptMessageHandler
   */
  virtual void RunJavaScriptMessageHandler( const std::string& objectName, const std::string& message ) = 0;
};

/**
 * @brief A class implements WebViewContainerClient and Dali::WebEnginePlugin for tizen chromium.
 */
class TizenWebEngineChromium : public Dali::WebEnginePlugin, public WebViewContainerClient
{

public:

  typedef std::function< void(const std::string&) > JavaScriptCallback;

  /**
   * @brief Constructor.
   */
  TizenWebEngineChromium();

  /**
   * @brief Destructor.
   */
  ~TizenWebEngineChromium() override;


  // WebEnginePlugin Interface


  /**
   * @copydoc Dali::WebEnginePlugin::Create()
   */
  void Create( int width, int height, const std::string& locale, const std::string& timezoneID ) override;

  /**
   * @copydoc Dali::WebEnginePlugin::Destroy()
   */
  void Destroy() override;

  /**
   * @copydoc Dali::WebEnginePlugin::LoadUrl()
   */
  void LoadUrl( const std::string& url ) override;

  /**
   * @copydoc Dali::WebEnginePlugin::GetNativeImageSource()
   */
  NativeImageInterfacePtr GetNativeImageSource() override;

  /**
   * @copydoc Dali::WebEnginePlugin::GetUrl()
   */
  const std::string& GetUrl() override;

  /**
   * @copydoc Dali::WebEnginePlugin::LoadHTMLString()
   */
  void LoadHTMLString( const std::string& string ) override;

  /**
   * @copydoc Dali::WebEnginePlugin::Reload()
   */
  void Reload() override;

  /**
   * @copydoc Dali::WebEnginePlugin::StopLoading()
   */
  void StopLoading() override;

  /**
   * @copydoc Dali::WebEnginePlugin::Suspend()
   */
  void Suspend() override;

  /**
   * @copydoc Dali::WebEnginePlugin::Resume()
   */
  void Resume() override;

  /**
   * @copydoc Dali::WebEnginePlugin::CanGoForward()
   */
  bool CanGoForward() override;

  /**
   * @copydoc Dali::WebEnginePlugin::GoForward()
   */
  void GoForward() override;

  /**
   * @copydoc Dali::WebEnginePlugin::CanGoBack()
   */
  bool CanGoBack() override;

  /**
   * @copydoc Dali::WebEnginePlugin::GoBack()
   */
  void GoBack() override;

  /**
   * @copydoc Dali::WebEnginePlugin::EvaluateJavaScript()
   */
  void EvaluateJavaScript( const std::string& script, std::function< void( const std::string& ) > resultHandler ) override;

  /**
   * @copydoc Dali::WebEnginePlugin::AddJavaScriptMessageHandler()
   */
  void AddJavaScriptMessageHandler( const std::string& exposedObjectName, std::function< void( const std::string& ) > handler ) override;

  /**
   * @copydoc Dali::WebEnginePlugin::ClearHistory()
   */
  void ClearHistory() override;

  /**
   * @copydoc Dali::WebEnginePlugin::ClearCache()
   */
  void ClearCache() override;

  /**
   * @copydoc Dali::WebEnginePlugin::ClearCookies()
   */
  void ClearCookies() override;

  /**
   * @copydoc Dali::WebEnginePlugin::GetCacheModel()
   */
  Dali::WebEnginePlugin::CacheModel GetCacheModel() const override;

  /**
   * @copydoc Dali::WebEnginePlugin::SetCacheModel()
   */
  void SetCacheModel( Dali::WebEnginePlugin::CacheModel cacheModel ) override;

  /**
   * @copydoc Dali::WebEnginePlugin::GetCookieAcceptPolicy()
   */
  Dali::WebEnginePlugin::CookieAcceptPolicy GetCookieAcceptPolicy() const override;

  /**
   * @copydoc Dali::WebEnginePlugin::SetCookieAcceptPolicy()
   */
  void SetCookieAcceptPolicy( Dali::WebEnginePlugin::CookieAcceptPolicy policy ) override;

  /**
   * @copydoc Dali::WebEnginePlugin::GetUserAgent()
   */
  const std::string& GetUserAgent() const override;

  /**
   * @copydoc Dali::WebEnginePlugin::SetUserAgent()
   */
  void SetUserAgent( const std::string& userAgent ) override;

  /**
   * @copydoc Dali::WebEnginePlugin::IsJavaScriptEnabled()
   */
  bool IsJavaScriptEnabled() const override;

  /**
   * @copydoc Dali::WebEnginePlugin::EnableJavaScript()
   */
  void EnableJavaScript( bool enabled ) override;

  /**
   * @copydoc Dali::WebEnginePlugin::AreImagesAutomaticallyLoaded()
   */
  bool AreImagesAutomaticallyLoaded() const override;

  /**
   * @copydoc Dali::WebEnginePlugin::LoadImagesAutomatically()
   */
  void LoadImagesAutomatically( bool automatic ) override;

  /**
   * @copydoc Dali::WebEnginePlugin::GetDefaultTextEncodingName()
   */
  const std::string& GetDefaultTextEncodingName() const override;

  /**
   * @copydoc Dali::WebEnginePlugin::SetDefaultTextEncodingName()
   */
  void SetDefaultTextEncodingName( const std::string& defaultTextEncodingName ) override;

  /**
   * @copydoc Dali::WebEnginePlugin::GetDefaultFontSize()
   */
  int GetDefaultFontSize() const override;

  /**
   * @copydoc Dali::WebEnginePlugin::SetDefaultFontSize()
   */
  void SetDefaultFontSize( int defaultFontSize ) override;

  /**
   * @copydoc Dali::WebEnginePlugin::SetSize()
   */
  void SetSize( int width, int height ) override;

  /**
   * @copydoc Dali::WebEnginePlugin::SendTouchEvent()
   */
  bool SendTouchEvent( const Dali::TouchEvent& touch ) override;

  /**
   * @copydoc Dali::WebEnginePlugin::SendKeyEvent()
   */
  bool SendKeyEvent( const Dali::KeyEvent& event ) override;

  /**
   * @copydoc Dali::WebEnginePlugin::PageLoadStartedSignal()
   */
  Dali::WebEnginePlugin::WebEnginePageLoadSignalType& PageLoadStartedSignal() override;

  /**
   * @copydoc Dali::WebEnginePlugin::PageLoadFinishedSignal()
   */
  Dali::WebEnginePlugin::WebEnginePageLoadSignalType& PageLoadFinishedSignal() override;

  /**
   * @copydoc Dali::WebEnginePlugin::PageLoadErrorSignal()
   */
  Dali::WebEnginePlugin::WebEnginePageLoadErrorSignalType& PageLoadErrorSignal() override;


  // WebViewContainerClient Interface


  /**
   * @copydoc Dali::Plugin::WebViewContainerClient::UpdateImage()
   */
  void UpdateImage( tbm_surface_h buffer ) override;

  /**
   * @copydoc Dali::Plugin::WebViewContainerClient::LoadStarted()
   */
  void LoadStarted() override;

  /**
   * @copydoc Dali::Plugin::WebViewContainerClient::LoadFinished()
   */
  void LoadFinished() override;

  /**
   * @copydoc Dali::Plugin::WebViewContainerClient::LoadError()
   */
  void LoadError( const char* url, int errorCode ) override;

  /**
   * @copydoc Dali::Plugin::WebViewContainerClient::RunJavaScriptEvaluationResultHandler()
   */
  void RunJavaScriptEvaluationResultHandler( size_t key, const char* result ) override;

  /**
   * @copydoc Dali::Plugin::WebViewContainerClient::RunJavaScriptMessageHandler()
   */
  void RunJavaScriptMessageHandler( const std::string& objectName, const std::string& message ) override;

private:

  WebViewContainerForDali*                                mWebViewContainer;
  Dali::NativeImageSourcePtr                              mDaliImageSrc;
  std::string                                             mUrl;
  size_t                                                  mJavaScriptEvaluationCount;

  Dali::WebEnginePlugin::WebEnginePageLoadSignalType      mLoadStartedSignal;
  Dali::WebEnginePlugin::WebEnginePageLoadSignalType      mLoadFinishedSignal;
  Dali::WebEnginePlugin::WebEnginePageLoadErrorSignalType mLoadErrorSignal;

  std::unordered_map< size_t, JavaScriptCallback >        mJavaScriptEvaluationResultHandlers;
  std::unordered_map< std::string, JavaScriptCallback >   mJavaScriptMessageHandlers;
};
} // namespace Plugin
} // namespace Dali

#endif
