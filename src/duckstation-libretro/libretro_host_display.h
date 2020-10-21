#pragma once
#include "core/host_display.h"
#include "libretro.h"

class LibretroHostDisplay final : public HostDisplay
{
public:
  LibretroHostDisplay();
  ~LibretroHostDisplay();

  RenderAPI GetRenderAPI() const override;
  void* GetRenderDevice() const override;
  void* GetRenderContext() const override;

  bool HasRenderDevice() const override;
  bool HasRenderSurface() const override;

  bool CreateRenderDevice(const WindowInfo& wi, std::string_view adapter_name, bool debug_device) override;
  bool InitializeRenderDevice(std::string_view shader_cache_directory, bool debug_device) override;
  void DestroyRenderDevice() override;

  bool MakeRenderContextCurrent() override;
  bool DoneRenderContextCurrent() override;

  bool ChangeRenderWindow(const WindowInfo& wi) override;
  void ResizeRenderWindow(s32 new_window_width, s32 new_window_height) override;
  void DestroyRenderSurface() override;

  bool SetPostProcessingChain(const std::string_view& config) override;

  bool CreateResources() override;
  void DestroyResources() override;

  std::unique_ptr<HostDisplayTexture> CreateTexture(u32 width, u32 height, const void* data, u32 data_stride,
                                                    bool dynamic) override;
  void UpdateTexture(HostDisplayTexture* texture, u32 x, u32 y, u32 width, u32 height, const void* data,
                     u32 data_stride) override;
  bool DownloadTexture(const void* texture_handle, u32 x, u32 y, u32 width, u32 height, void* out_data,
                       u32 out_data_stride) override;

  void SetVSync(bool enabled) override;

  bool Render() override;

  bool BeginSetDisplayPixels(DisplayPixelFormat format, u32 width, u32 height, void** out_buffer,
                             u32* out_pitch) override;
  void EndSetDisplayPixels() override;

  bool SetDisplayPixels(DisplayPixelFormat format, u32 width, u32 height, const void* buffer, u32 pitch) override;

private:
  std::vector<u32> m_frame_buffer;
  u32 m_frame_buffer_pitch = 0;
  retro_framebuffer m_software_fb = {};
};
